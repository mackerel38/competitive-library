---
title: Gaussian Integer
documentation_of: //math/gaussian_integer.hpp
---

## 概要

ガウス整数 `a + bi` と Euclid 互除法による gcd を提供します。

## 使い方

```cpp
#include "math/gaussian_integer.hpp"

auto g = poe::gaussian_gcd({a, b}, {c, d});
```

## 計算量

Euclid 互除法の反復回数に依存します。

