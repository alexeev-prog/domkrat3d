"""
Advanced static code analysis for C++ projects with legacy pattern detection,
memory management checks, and code structure analysis.
"""

import argparse
import re
import ast
from abc import ABC, abstractmethod
from pathlib import Path
from typing import Dict, List, Pattern, Optional, Set, Any
import logging
import multiprocessing
import json

class CodeAnalysisError(Exception):
    """Base exception for code analysis errors"""

class BaseCppAnalyzer(ABC):
    """Abstract base class for C++ code analysis with configurable rules"""
    
    def __init__(self, config: Dict[str, Any]):
        self.config = config
        self.logger = logging.getLogger(self.__class__.__name__)
        self._patterns = self._compile_patterns()
        self._validate_config()

    def _validate_config(self) -> None:
        if not Path(self.config['source_path']).exists():
            raise CodeAnalysisError(f"Invalid source path: {self.config['source_path']}")

    @abstractmethod
    def _compile_patterns(self) -> Dict[str, Pattern]:
        """Compile regex patterns for analysis"""

    @abstractmethod
    def analyze(self) -> Dict[str, Any]:
        """Perform code analysis"""

class CppLegacyAnalyzer(BaseCppAnalyzer):
    """Advanced legacy code pattern detector with configurable rules"""
    
    def _compile_patterns(self) -> Dict[str, Pattern]:
        return {
            'raw_pointers': re.compile(r'\b\w+\s*\*\s*\w+\b'),
            'c_headers': re.compile(r'#include\s+<(stdio|stdlib|string)\.h>'),
            'c_style_cast': re.compile(r'\((int|long|double|float|char)\)\s*\w+'),
            'old_style_functions': re.compile(r'\bvoid\s+\w+\s*\([^)]*\)\s*\{'),
            'macro_constants': re.compile(r'#define\s+[A-Z0-9_]+\s+[0-9]+'),
            'unsafe_functions': re.compile(r'\b(gets|strcpy|sprintf)\s*\('),
            'exception_spec': re.compile(r'\bthrow\s*\([^)]*\)'),
            'old_style_initialization': re.compile(r'\b\w+\s+\w+\s*=\s*\{?[^}]+\}?;'),
        }

    def analyze(self) -> Dict[str, Any]:
        results = {pattern: [] for pattern in self._patterns}
        files = self._get_target_files()
        
        with multiprocessing.Pool() as pool:
            tasks = [(file, self._patterns) for file in files]
            for file, matches in pool.imap_unordered(self._analyze_file, tasks):
                for pattern, instances in matches.items():
                    results[pattern].extend(instances)
        
        return results

    def _get_target_files(self) -> List[Path]:
        source_path = Path(self.config['source_path'])
        if source_path.is_file():
            return [source_path]
        return list(source_path.rglob('*.[ch]pp'))

    def _analyze_file(self, args: tuple) -> tuple:
        file, patterns = args
        matches = {}
        try:
            with open(file, 'r', encoding='utf-8') as f:
                content = f.read()
                for name, pattern in patterns.items():
                    matches[name] = self._find_matches(content, file, pattern)
        except UnicodeDecodeError:
            self.logger.warning("Skipping binary file: %s", file)
        return (file, matches)

    # ... (rest of implementation with detailed pattern matching)

def main():
    """Command line interface for C++ analysis"""
    parser = argparse.ArgumentParser(description='Advanced C++ Code Analyzer')
    parser.add_argument('path', help='File or directory to analyze')
    parser.add_argument('-c', '--config', help='Configuration file')
    parser.add_argument('-o', '--output', help='Output file (JSON format)')
    args = parser.parse_args()

    config = {
        'source_path': args.path,
        'analysis_types': ['legacy', 'memory'],
        'parallel_processing': True
    }
    
    try:
        analyzer = CppLegacyAnalyzer(config)
        report = analyzer.analyze()
        
        if args.output:
            with open(args.output, 'w') as f:
                json.dump(report, f, indent=2)
        else:
            print(json.dumps(report, indent=2))
            
    except CodeAnalysisError as e:
        logging.error(f"Analysis failed: {str(e)}")
        exit(1)

if __name__ == "__main__":
    main()
