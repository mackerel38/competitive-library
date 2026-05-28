---
title: Kth Root Mod
documentation_of: //math/kth_root_mod.hpp
---

## 概要

素数 mod `p` で `x^k = a (mod p)` を満たす `x` を返します。存在しなければ `-1` です。

## 使い方

```cpp
#include "math/kth_root_mod.hpp"

long long x = poe::kth_root_mod(a, k, p);
```

## 計算量

原始根と離散対数を使うため、主に `O(sqrt p)` です。

