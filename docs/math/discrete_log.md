---
title: Discrete Logarithm
documentation_of: //math/discrete_log.hpp
---

## 概要

`a^x = b (mod m)` を満たす最小の非負整数 `x` を返します。存在しなければ `-1` です。

## 使い方

```cpp
#include "math/discrete_log.hpp"

long long x = poe::discrete_log(a, b, mod);
```

## 計算量

Baby-step Giant-step により `O(sqrt mod)` です。

