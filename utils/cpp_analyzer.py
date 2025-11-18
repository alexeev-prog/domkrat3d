"""Advanced C++ code analysis with configurable rules and JSON output."""

import argparse
import json
import logging
import multiprocessing
import re
import sys
from pathlib import Path
from re import Pattern
from typing import Any

logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(name)s - %(levelname)s - %(message)s"
)


class CodeAnalysisError(Exception):
    """Base exception for code analysis failures."""


class CppCodeInspector:
    """Comprehensive C++ code analyzer with legacy pattern detection."""

    def __init__(self, config_path: str = "cpp_analysis.json"):
        self.config = self._load_config(config_path)
        self.logger = logging.getLogger(__name__)
        self.patterns = self._compile_patterns()

    def _load_config(self, config_path: str) -> dict[str, Any]:
        """Load JSON configuration with fallback."""
        try:
            with open(config_path, encoding="utf-8") as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            # self.logger.warning("Using default config: %s", str(e))
            return {
                "legacy_patterns": {"c_headers": True, "cstyle_casts": True},
                "file_extensions": [".cpp", ".hpp"],
                "exclude_dirs": ["build", "third_party"],
            }

    def _compile_patterns(self) -> dict[str, Pattern]:
        """Compile regex patterns based on config."""
        patterns = {}
        if self.config.get("legacy_patterns", {}).get("c_headers"):
            patterns["c_headers"] = re.compile(
                r"#include\s+<(stdio|stdlib|cstdlib)\.h>"
            )
        return patterns

    def analyze_directory(self, path: str) -> dict[str, Any]:
        """Analyze all C++ files in directory."""
        try:
            target_path = Path(path).resolve()
            if not target_path.exists():
                raise CodeAnalysisError(f"Path not found: {target_path}")

            files = self._collect_files(target_path)
            return self._process_files(files)
        except KeyboardInterrupt:
            raise CodeAnalysisError("Analysis interrupted by user")

    def _collect_files(self, path: Path) -> set[Path]:
        """Collect files respecting config rules."""
        all_files = set()
        for ext in self.config["file_extensions"]:
            all_files.update(path.rglob(f"*{ext}"))

        return {
            f
            for f in all_files
            if not any(d in f.parts for d in self.config["exclude_dirs"])
        }

    def _process_files(self, files: set[Path]) -> dict[str, Any]:
        """Process files using multiprocessing."""
        with multiprocessing.Pool() as pool:
            results = pool.map(self._analyze_file, files)

        report = {pattern: [] for pattern in self.patterns}
        for file_result in results:
            for pattern, matches in file_result.items():
                report[pattern].extend(matches)

        return report

    def _analyze_file(self, file_path: Path) -> dict[str, list[str]]:
        """Analyze single file for legacy patterns."""
        results = {pattern: [] for pattern in self.patterns}
        try:
            with open(file_path, encoding="utf-8") as f:
                content = f.read()
                for pattern_name, regex in self.patterns.items():
                    matches = regex.findall(content)
                    if matches:
                        results[pattern_name].extend(
                            [f"{file_path}:{i + 1}" for i, _ in enumerate(matches)]
                        )
        except UnicodeDecodeError:
            self.logger.warning("Skipping binary file: %s", file_path)
        return results


def main():
    """Command line interface for code analysis."""
    parser = argparse.ArgumentParser(
        description="Analyze C++ code for legacy patterns",
        epilog="Example: python cpp_analyzer.py src/ -c config.json",
    )
    parser.add_argument("path", help="File or directory to analyze")
    parser.add_argument(
        "-c", "--config", default="cpp_analysis.json", help="Configuration file path"
    )
    parser.add_argument("-o", "--output", help="Output JSON file path")

    args = parser.parse_args()

    try:
        inspector = CppCodeInspector(args.config)
        report = inspector.analyze_directory(args.path)

        if args.output:
            with open(args.output, "w", encoding="utf-8") as f:
                json.dump(report, f, indent=2)
            print(f"Analysis saved to {args.output}")
        else:
            print(json.dumps(report, indent=2))

    except CodeAnalysisError as e:
        logging.exception("Analysis failed: %s", str(e))
        sys.exit(1)


if __name__ == "__main__":
    main()
