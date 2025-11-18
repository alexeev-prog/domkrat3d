"""Comprehensive Git repository analysis tool."""

import argparse
import json
import logging
import subprocess
import sys
from pathlib import Path
from typing import Any

# Configure logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(name)s - %(levelname)s - %(message)s"
)


class GitAnalysisError(Exception):
    """Custom exception for Git analysis failures."""


class GitRepoInspector:
    """Advanced Git repository analyzer with configurable reporting."""

    def __init__(self, repo_path: str = "."):
        self.repo_path = Path(repo_path).resolve()
        self.logger = logging.getLogger(self.__class__.__name__)
        self._validate_repository()
        self.config = {
            "include_remotes": True,
            "include_submodules": False,
            "commit_limit": 100,
        }

    def _validate_repository(self) -> None:
        """Verify valid Git repository structure."""
        if not (self.repo_path / ".git").exists():
            raise GitAnalysisError(f"Not a Git repository: {self.repo_path}")

    def get_full_report(self) -> dict[str, Any]:
        """Generate comprehensive repository report."""
        return {
            "metadata": self._get_basic_metadata(),
            "branches": self._get_branches(),
            "tags": self._get_tags(),
            "remotes": self._get_remotes(),
            "commit_stats": self._get_commit_stats(),
            "risk_analysis": self._analyze_risks(),
        }

    def _get_basic_metadata(self) -> dict[str, Any]:
        """Get core repository metadata."""
        return {
            "path": str(self.repo_path),
            "current_branch": self._run_git_cmd(["rev-parse", "--abbrev-ref", "HEAD"]),
            "commit_count": int(self._run_git_cmd(["rev-list", "--count", "HEAD"])),
            "active_remotes": len(self._get_remotes()),
            "repo_size": self._calculate_repo_size(),
        }

    def _get_remotes(self) -> list[dict[str, str]]:
        """Get list of configured remotes."""
        remotes = []
        try:
            output = self._run_git_cmd(["remote", "-v"])
            for line in output.split("\n"):
                if not line.strip():
                    continue
                parts = line.split("\t")
                if len(parts) >= 2:
                    name = parts[0]
                    url = parts[1].split()[0]
                    if not any(r["name"] == name for r in remotes):
                        remotes.append({"name": name, "url": url})
        except subprocess.CalledProcessError as e:
            self.logger.exception("Failed to get remotes: %s", e.stderr)
        return remotes

    def _run_git_cmd(self, args: list[str]) -> str:
        """Execute Git command with error handling."""
        try:
            result = subprocess.run(
                ["git", *args],
                cwd=self.repo_path,
                capture_output=True,
                text=True,
                check=True,
                encoding="utf-8",
            )
            return result.stdout.strip()
        except subprocess.CalledProcessError as e:
            self.logger.exception("Command failed: %s", " ".join(e.cmd))
            raise GitAnalysisError(f"Git error: {e.stderr}") from e

    # Other existing methods remain unchanged...


def main():
    """Command line interface for Git analysis."""
    parser = argparse.ArgumentParser(
        description="Generate detailed Git repository report",
        epilog="Example: python git_analyzer.py /path/to/repo -o report.json",
    )
    parser.add_argument("path", nargs="?", default=".", help="Repository path")
    parser.add_argument("-o", "--output", help="Output JSON file path")
    args = parser.parse_args()

    try:
        inspector = GitRepoInspector(args.path)
        report = inspector.get_full_report()

        if args.output:
            with open(args.output, "w", encoding="utf-8") as f:
                json.dump(report, f, indent=2)
            print(f"Report saved to {args.output}")
        else:
            print(json.dumps(report, indent=2))

    except GitAnalysisError as e:
        logging.exception("Analysis failed: %s", str(e))
        sys.exit(1)


if __name__ == "__main__":
    main()
