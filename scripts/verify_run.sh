#!/usr/bin/env bash
set -euo pipefail

commit_message="${1:-Verify library updates}"

oj-verify run
oj-verify docs

if ! git diff --quiet || ! git diff --cached --quiet; then
    git add -A
    git commit -m "$commit_message"
else
    echo "No changes to commit."
fi

current_branch="$(git branch --show-current)"
if [[ -z "$current_branch" ]]; then
    echo "Cannot push because the current HEAD is detached." >&2
    exit 1
fi

if git rev-parse --abbrev-ref --symbolic-full-name '@{u}' >/dev/null 2>&1; then
    git pull --ff-only
fi

git push -u origin "$current_branch"
git pull --ff-only
