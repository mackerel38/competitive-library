# competitive-library

C++23 competitive programming library for personal use.

## Requirements

- C++23 compiler, primarily `g++`
- `online-judge-verify-helper` (`oj-verify`)

## Directory Layout

- `structure/`: data structures
- `math/`: number theory and algebra
- `geometry/`: geometry utilities
- `string/`: string algorithms
- `utility/`: small helpers and common utilities
- `graph/`: graph algorithms and data structures
- `verify/`: verification programs for `oj-verify`

## Include Policy

Headers are included from the repository root.

```cpp
#include "math/modint.hpp"
```

Verification files and local contest code should compile with the repository
root added to the include path.

## Verification

Run all verification files:

```sh
oj-verify run
```

Build documentation if needed:

```sh
oj-verify docs
```

