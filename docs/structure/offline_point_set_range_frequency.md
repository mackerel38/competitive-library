---
title: Offline Point Set Range Frequency
documentation_of: //structure/offline_point_set_range_frequency.hpp
---

## 概要

点代入と区間内の値の出現回数クエリを扱うオフライン構造です。初期配列と、将来 `set(pos, value)` で現れる組を先に渡して構築します。

## メソッド

- `offline_point_set_range_frequency(initial, future_sets)`: 初期配列と将来の代入候補を渡して構築します。
- `set(p, value)`: `a[p] = value` に更新します。`value` は構築時に渡した値である必要があります。
- `count(l, r, value)`: `[l, r)` に含まれる `value` の個数を返します。
- `get(p)`: 現在の `a[p]` を返します。
- `size()`: 配列長を返します。

## 計算量

構築は `O((N + U) log (N + U))`、更新とクエリは `O(log N + log sigma)` です。`U` は将来代入の数、`sigma` は値の種類数です。
