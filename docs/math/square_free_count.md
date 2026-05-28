---
title: Square Free Count
documentation_of: //math/square_free_count.hpp
---

## 概要

`n` 以下の square-free な正整数の個数を返します。

## 使い方

```cpp
#include "math/square_free_count.hpp"

long long ans = poe::count_square_free(n);
```

## 計算量

`O(sqrt N)` です。

