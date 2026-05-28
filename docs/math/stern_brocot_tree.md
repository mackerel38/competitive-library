---
title: Stern-Brocot Tree
documentation_of: //math/stern_brocot_tree.hpp
---

## 概要

正の既約分数の Stern-Brocot path を run-length 形式で扱います。

## 使い方

```cpp
#include "math/stern_brocot_tree.hpp"

auto path = poe::stern_brocot_path(p, q);
auto frac = poe::stern_brocot_restore(path);
```

## 計算量

Euclid の互除法に対応し、`O(log max(p, q))` 程度です。

