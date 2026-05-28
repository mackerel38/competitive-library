---
title: Nim Product
documentation_of: //math/nim_product.hpp
---

## 概要

64 bit 非負整数の Nim product を計算します。

## 使い方

```cpp
#include "math/nim_product.hpp"

auto z = poe::nim_product(x, y);
```

## 注意

8 bit の表を遅延初期化し、64 bit までは再帰分割で計算します。
`nim_product(0, x) = 0`、`nim_product(1, x) = x` です。

## 計算量

初回は 8 bit 表の構築に定数時間がかかります。1 クエリは再帰分割の定数個演算で、
64 bit 固定なので実用上 `O(1)` です。
