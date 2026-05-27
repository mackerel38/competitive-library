---
title: Ordered Set
documentation_of: //structure/ordered_set.hpp
---

## 概要

乱択 Treap による順序付き集合です。重複しないキーを管理し、挿入・削除・順位・k 番目取得・前駆後継のための二分探索系メソッドを提供します。

## メソッド

- `insert(x)`: `x` を追加します。新しく追加したら `true` を返します。
- `erase(x)`: `x` を削除します。存在して削除したら `true` を返します。
- `contains(x)`: `x` が存在するかを返します。
- `order_of_key(x)`, `count_lt(x)`: `x` 未満の要素数を返します。
- `count_le(x)`, `count_ge(x)`, `count_gt(x)`: それぞれ `<= x`, `>= x`, `> x` の要素数を返します。
- `kth(k)`: 0-indexed で `k` 番目に小さい値を返します。
- `lower_bound(x)`: `x` 以上の最小値を返します。存在することを `assert` します。
- `upper_bound(x)`: `x` より大きい最小値を返します。存在することを `assert` します。
- `min()`, `max()`: 最小値・最大値を返します。空でないことを `assert` します。

## 計算量

各操作は期待 `O(log N)` です。
