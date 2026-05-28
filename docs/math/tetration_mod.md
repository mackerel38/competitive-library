---
title: Tetration Mod
documentation_of: //math/tetration_mod.hpp
---

## 概要

高さ `h` の冪塔 `a^(a^(...)) mod m` を求めます。

## 使い方

```cpp
#include "math/tetration_mod.hpp"

long long x = poe::tetration_mod(a, h, m);
```

## 計算量

高さと `m` の素因数分解に依存します。

