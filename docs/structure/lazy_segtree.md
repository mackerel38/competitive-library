---
title: Lazy Segment Tree
documentation_of: //structure/lazy_segtree.hpp
---

## 概要

遅延伝播 Segment Tree です。区間作用と区間取得を扱います。ACL と同じく、モノイド `S`、作用 `F`、`mapping`, `composition`, `id` を渡します。

## メソッド

- `set(p, x)`, `get(p)`: 点代入、点取得。
- `prod(l, r)`: `[l, r)` の積を返します。
- `all_prod()`: 全体の積を返します。
- `apply(p, f)`: 点に作用 `f` を適用します。
- `apply(l, r, f)`: `[l, r)` に作用 `f` を適用します。
- `max_right(l, g)`, `min_left(r, g)`: Segment Tree 上の二分探索を行います。

## 計算量

構築は `O(N)`、`set`, `get`, `prod`, `apply`, `max_right`, `min_left` は `O(log N)` です。
