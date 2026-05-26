---
title: Segment Tree
documentation_of: //structure/segtree.hpp
---

## 概要

モノイドの Segment Tree です。ACL と同じ形で `op` と単位元 `e` を渡します。

## 使い方

```cpp
#include "structure/segtree.hpp"

int op(int a, int b) { return std::min(a, b); }
int e() { return 1 << 30; }

poe::segtree<int, op, e> seg(v);
int x = seg.prod(l, r);
```

## メソッド

- `set(p, x)`: `a[p] = x`。
- `get(p)`: `a[p]` を返します。
- `prod(l, r)`: `[l, r)` の積を返します。
- `all_prod()`: 全体の積を返します。
- `max_right(l, f)`: `f(prod(l, r))` が成り立つ最大の右端を二分探索します。
- `min_left(r, f)`: `f(prod(l, r))` が成り立つ最小の左端を二分探索します。

## 計算量

構築は `O(N)`、`set`, `prod`, `max_right`, `min_left` は `O(log N)`、`get`, `all_prod` は `O(1)` です。
