---
title: Integer Kth Root
documentation_of: //math/integer_kth_root.hpp
---

## 概要

`x^k <= n` を満たす最大の整数 `x` を返します。

## 使い方

```cpp
#include "math/integer_kth_root.hpp"

auto x = poe::integer_kth_root(n, k);
```

## 計算量

`O(k log n)` です。内部では `__uint128_t` で overflow を避けます。

