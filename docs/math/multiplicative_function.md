---
title: Multiplicative Function
documentation_of: //math/multiplicative_function.hpp
---

## 概要

乗法的関数の補助です。現在は `sum_totient<T>(n)` と `totient_sum<T>` を提供します。

## 使い方

```cpp
#include "math/multiplicative_function.hpp"

auto s = poe::sum_totient<poe::modint998244353>(n);
```

## 計算量

商の値ごとにメモ化して `O(sqrt N)` 個程度の状態を処理します。

