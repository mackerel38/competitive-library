---
title: Bernoulli Number
documentation_of: //math/bernoulli.hpp
---

## 概要

Bernoulli number `B_0, ..., B_n` を modint で計算します。

## 使い方

```cpp
#include "math/bernoulli.hpp"

auto b = poe::bernoulli_numbers<poe::modint998244353>(n);
```

## 計算量

現在の実装は Akiyama-Tanigawa による `O(N^2)` です。

