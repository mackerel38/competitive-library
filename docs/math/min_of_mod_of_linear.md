---
title: Min of Mod of Linear
documentation_of: //math/min_of_mod_of_linear.hpp
---

## 概要

`min_{0 <= i < n} (a i + b) mod m` を返します。

## 使い方

```cpp
#include "math/min_of_mod_of_linear.hpp"

long long ans = poe::min_of_mod_of_linear(n, m, a, b);
```

## 計算量

`O(log max(a, b, m, n))` 程度です。

## 注意

`n >= 0`、`m >= 1` を仮定します。`n = 0` のときは `0` を返します。
`a` と `b` は内部で `m` で正規化します。
