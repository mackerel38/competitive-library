---
title: Offline Range Majority
documentation_of: //structure/offline_range_majority.hpp
---

## 概要

点代入と区間 majority クエリを扱うオフライン構造です。Boyer-Moore の候補モノイドを Segment Tree で管理し、候補の実出現回数を `offline_point_set_range_frequency` で検証します。

## メソッド

- `offline_range_majority(initial, future_sets)`: 初期配列と将来の代入候補を渡して構築します。
- `set(p, value)`: `a[p] = value` に更新します。
- `majority(l, r)`: `[l, r)` に半数より多く出現する値があれば `std::optional<T>` で返し、なければ `std::nullopt` を返します。
- `count(l, r, value)`: `[l, r)` に含まれる `value` の個数を返します。

## 計算量

構築は `O((N + U) log (N + U))`、更新とクエリは `O(log N + log sigma)` です。
