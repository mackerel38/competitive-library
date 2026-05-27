---
title: Weighted DSU
documentation_of: //structure/weighted_dsu.hpp
---

## 概要

各頂点にポテンシャルを持つ Union-Find です。`weighted_dsu<T>` は加法群を扱い、`merge(x, y, w)` で `weight(y) - weight(x) = w` という制約を追加します。

非可換群向けに `weighted_dsu_group<G, op, inv, e>` も用意しています。

## メソッド

- `leader(x)`: `x` の代表元を返します。
- `same(x, y)`: `x`, `y` が同じ連結成分に属するかを返します。
- `merge(x, y, w)`: `weight(y) - weight(x) = w` を追加します。矛盾しなければ `true`、矛盾すれば `false` を返します。
- `weight(x)`: 代表元から見た `x` のポテンシャルを返します。
- `diff(x, y)`: `weight(y) - weight(x)` を返します。同じ連結成分であることを `assert` します。
- `size(x)`: `x` を含む連結成分のサイズを返します。

## 計算量

各操作はならし `O(alpha(N))` です。
