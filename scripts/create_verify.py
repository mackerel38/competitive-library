#!/usr/bin/env python3
import re
import sys
from pathlib import Path
from urllib.parse import urlparse


def sanitize_name(name: str) -> str:
    name = re.sub(r"[^A-Za-z0-9_+-]+", "_", name.strip())
    name = name.strip("_")
    return name or "problem"


def parse_problem_url(url: str) -> tuple[str, str]:
    parsed = urlparse(url)
    host = parsed.netloc.lower()
    parts = [part for part in parsed.path.split("/") if part]

    if "yosupo.jp" in host:
        if "problem" not in parts:
            raise ValueError("yosupo の問題リンクは /problem/<問題名> を含めてください。")
        index = parts.index("problem")
        if index + 1 >= len(parts):
            raise ValueError("yosupo の問題名を URL から読み取れません。")
        return "yosupo", sanitize_name(parts[index + 1])

    if "u-aizu.ac.jp" in host or "aoj" in host:
        if "problems" in parts:
            index = parts.index("problems")
            if index + 1 < len(parts):
                return "aoj", sanitize_name(parts[index + 1])
        if parts:
            return "aoj", sanitize_name(parts[-1])
        raise ValueError("AOJ の問題 ID を URL から読み取れません。")

    raise ValueError("AOJ または yosupo の問題リンクを指定してください。")


def main() -> None:
    if len(sys.argv) != 2:
        print("usage: scripts/create_verify.py <AOJ or yosupo problem URL>", file=sys.stderr)
        raise SystemExit(2)

    url = sys.argv[1]
    service, problem_name = parse_problem_url(url)

    repo_root = Path(__file__).resolve().parents[1]
    verify_dir = repo_root / "verify"
    verify_dir.mkdir(exist_ok=True)

    path = verify_dir / f"{service}_{problem_name}.test.cpp"
    if path.exists():
        print(f"already exists: {path}", file=sys.stderr)
        raise SystemExit(1)

    content = f'''#define PROBLEM "{url}"
#include <bits/stdc++.h>
using namespace std;

int main() {{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

}}
'''
    path.write_text(content, encoding="utf-8", newline="\n")
    print(path.relative_to(repo_root).as_posix())


if __name__ == "__main__":
    main()
