---
title: Dual Segment Tree
documentation_of: //structure/dual_segtree.hpp
---

## 概要

区間作用・点取得に特化した Dual Segment Tree です。`mapping(f, x)` と `composition(new_f, old_f)`、恒等作用 `id()` を定義して使います。

## メソッド

- `dual_segtree(v)`: 初期配列 `v` で構築します。
- `apply(l, r, f)`: `[l, r)` に作用 `f` を適用します。
- `apply(p, f)`: `p` に作用 `f` を適用します。
- `get(p)`: 適用済みの `a[p]` を返します。
- `set(p, x)`: 現在までの遅延作用を反映したうえで `a[p] = x` にします。
- `all_get()`: 全要素を取得します。

## 計算量

`apply` は `O(log N)`、`get` は `O(log N)`、`all_get` は `O(N log N)` です。
