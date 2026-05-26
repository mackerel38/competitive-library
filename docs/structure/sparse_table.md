---
title: Sparse Table
documentation_of: //structure/sparse_table.hpp
---

## 概要

静的配列に対する冪等半群の区間取得です。`min`, `max`, `gcd` など `op(x, x) = x` が成り立つ演算で使えます。

## メソッド

- `sparse_table(v)`: 配列 `v` から構築します。
- `get(p)`: `v[p]` を返します。
- `prod(l, r)`: `[l, r)` の演算結果を返します。空区間は扱いません。

## 計算量

構築は `O(N log N)`、`prod` は `O(1)` です。
