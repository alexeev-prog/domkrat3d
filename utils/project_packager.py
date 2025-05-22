"""
Advanced project packaging system with build automation, configurable inclusion rules,
and multiple output formats.
"""

import argparse
import tarfile
import subprocess
import json
import yaml
from pathlib import Path
from typing import Dict, List, Set, Optional
from datetime import datetime
import logging
import multiprocessing
import os

class PackagingError(Exception):
    """Custom exception for packaging failures"""

class ProjectPackager:
    """Intelligent project packager with build system integration"""
    
    def __init__(self, config: Dict[str, Any]):
        self.config = self._validate_config(config)
        self.logger = logging.getLogger(self.__class__.__name__)
        self._setup_paths()

    def _validate_config(self, config: Dict) -> Dict:
        defaults = {
            'build_command': ['./build.sh'],
            'include_files': {'README.*', 'LICENSE*'},
            'exclude_dirs': {'.git', 'build', 'dist'},
            'output_format': 'tar.xz',
            'parallel_jobs': multiprocessing.cpu_count(),
            'compression_level': 6
        }
        return {**defaults, **config}

    def _setup_paths(self) -> None:
        self.base_path = Path(self.config['base_dir']).resolve()
        os.chdir(self.base_path)

    def package(self) -> Path:
        """Main packaging workflow"""
        self._run_build()
        files = self._collect_files()
        return self._create_package(files)

    def _run_build(self) -> None:
        """Execute build system with error handling"""
        try:
            subprocess.run(
                self.config['build_command'],
                check=True,
                capture_output=True,
                text=True
            )
        except subprocess.CalledProcessError as e:
            raise PackagingError(f"Build failed: {e.stderr}")

    def _collect_files(self) -> Set[Path]:
        """Collect files using parallel processing"""
        with multiprocessing.Pool(self.config['parallel_jobs']) as pool:
            tasks = [(path, self.config) for path in self.base_path.rglob('*')]
            results = pool.starmap(self._process_path, tasks)
            
        return {path for path in results if path is not None}

    def _process_path(self, path: Path, config: Dict) -> Optional[Path]:
        if any(part in config['exclude_dirs'] for part in path.parts):
            return None
        if path.is_file() and self._should_include(path.name, config):
            return path
        return None

    def _should_include(self, filename: str, config: Dict) -> bool:
        return any(
            re.match(pattern, filename)
            for pattern in config['include_files']
        )

    def _create_package(self, files: Set[Path]) -> Path:
        """Create compressed archive with progress tracking"""
        timestamp = datetime.now().strftime('%Y%m%d-%H%M%S')
        pkg_name = f"{self.config['project_name']}_{timestamp}.{self.config['output_format']}"
        
        with tarfile.open(pkg_name, f'w:{self._get_compression()}') as tar:
            for file in files:
                tar.add(file, arcname=file.relative_to(self.base_path))
                
        return Path(pkg_name)

    # ... (rest of implementation with advanced features)

def load_config(config_path: str) -> Dict:
    """Load configuration from JSON/YAML file"""
    path = Path(config_path)
    if path.suffix == '.json':
        return json.loads(path.read_text())
    elif path.suffix in ('.yaml', '.yml'):
        return yaml.safe_load(path.read_text())
    raise PackagingError(f"Unsupported config format: {path.suffix}")

def main():
    """Command line interface for packaging"""
    parser = argparse.ArgumentParser(description='Advanced Project Packager')
    parser.add_argument('-c', '--config', default='packager.yaml', help='Config file')
    parser.add_argument('-o', '--output', help='Output file name')
    args = parser.parse_args()

    try:
        config = load_config(args.config)
        if args.output:
            config['output_format'] = Path(args.output).suffix[1:]
            
        packager = ProjectPackager(config)
        package_path = packager.package()
        print(f"Created package: {package_path}")
        
    except PackagingError as e:
        logging.error(f"Packaging failed: {str(e)}")
        exit(1)

if __name__ == "__main__":
    main()
