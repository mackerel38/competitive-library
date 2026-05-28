---
title: Two Square Sum
documentation_of: //math/two_square_sum.hpp
---

## 概要

`n = a^2 + b^2` の表現を 1 つ構成します。存在しなければ空列を返します。

## 使い方

```cpp
#include "math/two_square_sum.hpp"

auto v = poe::two_square_sum(n);
```

## 計算量

素因数分解と Cornacchia 型の構成に依存します。

