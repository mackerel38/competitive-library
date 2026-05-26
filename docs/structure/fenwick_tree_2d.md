---
title: Fenwick Tree 2D
documentation_of: //structure/fenwick_tree_2d.hpp
---

## 概要

2 次元 Fenwick Tree です。点加算と矩形和を扱います。密な `H * W` の表として使う方法と、更新される点を先に集めて座標圧縮する疎な方法があります。

## メソッド

- `fenwick_tree_2d(h, w)`: `h * w` の表を作ります。
- `fenwick_tree_2d(points)`: 更新される点集合 `points` をもとに座標圧縮して作ります。
- `build(points)`: 空のインスタンスを座標圧縮形式で構築します。
- `add(x, y, v)`: `a[x][y] += v`。
- `sum(x, y)`: dense 形式では `[0, x) * [0, y)`、座標圧縮形式では `x' < x`, `y' < y` の総和を返します。
- `sum(xl, xr, yl, yr)`, `range_sum(xl, xr, yl, yr)`: `[xl, xr) * [yl, yr)` の総和を返します。
- `get(x, y)`: `a[x][y]` を返します。
- `set(x, y, v)`: `a[x][y] = v`。

## 計算量

`add`, `sum`, `set`, `get` は `O(log H log W)` です。座標圧縮形式の構築は、更新候補点数を `M` として `O(M log M log H)` です。座標圧縮形式では `add`, `get`, `set` に使う点を事前に `points` に含める必要があります。
