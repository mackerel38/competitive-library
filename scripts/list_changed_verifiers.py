#!/usr/bin/env python3
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
VERIFY_DIR = ROOT / "verify"
INCLUDE_RE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.MULTILINE)
ZERO_SHA = "0" * 40


def git(*args: str) -> str:
    return subprocess.check_output(["git", *args], cwd=ROOT, text=True).strip()


def all_verifiers() -> list[Path]:
    return sorted(VERIFY_DIR.glob("*.test.cpp"))


def normalize(path: Path) -> str:
    return path.resolve().relative_to(ROOT).as_posix()


def changed_files(base: str, head: str) -> set[str] | None:
    if not base or base == ZERO_SHA:
        return None
    try:
        git("rev-parse", "--verify", base)
        git("rev-parse", "--verify", head)
        out = git("diff", "--name-only", base, head)
    except subprocess.CalledProcessError:
        return None
    return {line for line in out.splitlines() if line}


def local_includes(path: Path) -> list[Path]:
    try:
        text = path.read_text(errors="ignore")
    except OSError:
        return []
    result = []
    for include in INCLUDE_RE.findall(text):
        candidates = [ROOT / include, path.parent / include]
        for candidate in candidates:
            if candidate.exists():
                result.append(candidate.resolve())
                break
    return result


def dependency_closure(path: Path, memo: dict[Path, set[str]]) -> set[str]:
    path = path.resolve()
    if path in memo:
        return memo[path]
    deps = {normalize(path)}
    memo[path] = deps
    for included in local_includes(path):
        deps |= dependency_closure(included, memo)
    return deps


def main() -> None:
    base = sys.argv[1] if len(sys.argv) >= 2 else ""
    head = sys.argv[2] if len(sys.argv) >= 3 else "HEAD"
    changed = changed_files(base, head)
    verifiers = all_verifiers()
    if changed is None:
        targets = verifiers
    else:
        memo: dict[Path, set[str]] = {}
        targets = [
            verifier
            for verifier in verifiers
            if normalize(verifier) in changed
            or bool(dependency_closure(verifier, memo) & changed)
        ]
    for target in targets:
        print(normalize(target))


if __name__ == "__main__":
    main()
