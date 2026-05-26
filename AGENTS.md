# Repository Guidelines

## Purpose

This repository is a C++23 competitive programming library. Keep it small,
portable, and easy to copy into contest solutions.

## Implementation Rules

- Use C++23.
- Place headers directly under their category directories.
- Prefer include paths relative to the repository root, for example
  `#include "math/modint.hpp"`.
- Add or update verification programs under `verify/` when adding library code.
- Keep public APIs stable. Record breaking changes in `README.md`.
- Avoid unnecessary dependencies outside the C++ standard library.

## Verification

- Run `oj-verify run` before publishing changes.
- Verification files should be minimal and focused on one library component.
- Use `// competitive-verifier: PROBLEM ...` comments when binding a verifier to
  an online judge problem.

