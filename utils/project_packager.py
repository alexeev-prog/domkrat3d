"""Intelligent project packaging system with build automation and JSON config."""

import argparse
import json
import logging
import subprocess
import sys
import tarfile
from datetime import datetime
from pathlib import Path
from typing import Any

logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(name)s - %(levelname)s - %(message)s"
)


class PackagingError(Exception):
    """Custom exception for packaging failures."""


class ProjectPackager:
    """Advanced project packager with build system integration."""

    def __init__(self, config_path: str = "packager.json"):
        self.config = self._load_config(config_path)
        self.logger = logging.getLogger(self.__class__.__name__)
        self._validate_config()

    def _load_config(self, config_path: str) -> dict[str, Any]:
        """Load packaging configuration."""
        try:
            with open(config_path, encoding="utf-8") as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError) as e:
            raise PackagingError(f"Invalid config file: {e!s}")

    def _validate_config(self) -> None:
        """Validate configuration parameters."""
        required_keys = ["build_command", "include_files", "output_name"]
        missing = [k for k in required_keys if k not in self.config]
        if missing:
            raise PackagingError(f"Missing config keys: {', '.join(missing)}")

    def package(self) -> Path:
        """Execute full packaging workflow."""
        self._run_build()
        files = self._collect_files()
        return self._create_package(files)

    def _run_build(self) -> None:
        """Execute build system with validation."""
        build_script = Path(self.config["build_command"][0])
        if not build_script.exists():
            raise PackagingError(f"Build script not found: {build_script}")

        try:
            subprocess.run(
                self.config["build_command"], check=True, capture_output=True, text=True
            )
        except subprocess.CalledProcessError as e:
            raise PackagingError(f"Build failed: {e.stderr}")

    def _collect_files(self) -> set[Path]:
        """Collect files for packaging."""
        all_files = set()
        for pattern in self.config["include_files"]:
            all_files.update(Path().rglob(pattern))

        return {f for f in all_files if f.is_file() and not self._is_excluded(f)}

    def _is_excluded(self, path: Path) -> bool:
        """Check if path should be excluded."""
        return any(part in self.config.get("exclude_dirs", []) for part in path.parts)

    def _create_package(self, files: set[Path]) -> Path:
        """Create compressed archive."""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        pkg_name = f"{self.config['output_name']}_{timestamp}.tar.xz"

        with tarfile.open(pkg_name, "w:xz") as tar:
            for file in files:
                tar.add(file, arcname=file.relative_to(Path.cwd()))
                self.logger.info("Added: %s", file)

        return Path(pkg_name).resolve()


def main():
    """Command line interface for packaging."""
    parser = argparse.ArgumentParser(
        description="Package project with build automation",
        epilog="Example: python project_packager.py -c config.json",
    )
    parser.add_argument(
        "-c", "--config", default="packager.json", help="Configuration file path"
    )
    parser.add_argument("-o", "--output", help="Override output file name")

    args = parser.parse_args()

    try:
        packager = ProjectPackager(args.config)
        package_path = packager.package()
        print(f"Package created: {package_path}")

    except PackagingError as e:
        logging.exception("Packaging failed: %s", str(e))
        sys.exit(1)


if __name__ == "__main__":
    main()
