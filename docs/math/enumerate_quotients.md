---
title: Enumerate Quotients
documentation_of: //math/enumerate_quotients.hpp
---

## 概要

`floor(n / i)` が一定になる半開区間 `[l, r)` を列挙します。

## 使い方

```cpp
#include "math/enumerate_quotients.hpp"

for (auto [l, r, q] : poe::enumerate_quotients(n)) {
    // l <= i < r で n / i == q
}
```

## 計算量

列挙数を `K` として `O(K)` です。`K = O(sqrt N)` です。

