---
title: Mod Sqrt
documentation_of: //math/mod_sqrt.hpp
---

## 概要

素数 mod で `x^2 = a (mod p)` を満たす `x` を返します。解がなければ `-1` です。

## 使い方

```cpp
#include "math/mod_sqrt.hpp"

long long x = poe::mod_sqrt(a, p);
```

## 計算量

Tonelli-Shanks により `O(log^2 p)` 程度です。

