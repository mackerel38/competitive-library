---
title: Rollback DSU
documentation_of: //structure/rollback_dsu.hpp
---

## 概要

rollback できる DSU です。offline dynamic connectivity などで使います。経路圧縮は行わず、履歴を積んで戻します。

## メソッド

- `merge(a, b)`: 成分を併合し、実際に併合されたら `true`。
- `same(a, b)`, `leader(a)`, `size(a)`: 成分情報を返します。
- `components()`: 現在の成分数を返します。
- `snapshot()`: 現在時刻を返します。
- `rollback(t)`: 時刻 `t` まで戻します。
- `undo()`: 直前の `merge` を 1 回戻します。

## 計算量

`merge`, `same`, `leader`, `size` は `O(log N)`、`undo` は `O(1)`、`rollback(t)` は戻す回数に比例します。
