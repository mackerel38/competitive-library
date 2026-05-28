---
title: Prime Count
documentation_of: //math/prime_count.hpp
---

## 概要

`n` 以下の素数の個数 `pi(n)` を求めます。

## 使い方

```cpp
#include "math/prime_count.hpp"

long long ans = poe::prime_count(n);
```

## 計算量

`O(sqrt N)` 個程度のテーブルを使います。

