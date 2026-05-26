---
title: Wavelet Matrix
documentation_of: //structure/wavelet_matrix.hpp
---

## 概要

静的配列の区間 kth、rank、頻度、前駆・後継を扱う Wavelet Matrix です。値は座標圧縮して管理します。

## メソッド

- `access(k)`, `get(k)`: 元の `a[k]` を返します。
- `rank(r, x)`: `[0, r)` に含まれる `x` の個数を返します。
- `rank(l, r, x)`: `[l, r)` に含まれる `x` の個数を返します。
- `kth_smallest(l, r, k)`: `[l, r)` の `k` 番目に小さい値を返します。
- `kth_largest(l, r, k)`: `[l, r)` の `k` 番目に大きい値を返します。
- `range_freq(l, r, upper)`: `[l, r)` に含まれる `upper` 未満の値の個数を返します。
- `range_freq(l, r, lower, upper)`: `[l, r)` に含まれる `[lower, upper)` の個数を返します。
- `prev_value(l, r, upper)`: `upper` 未満で最大の値を返します。存在することを `assert` します。
- `next_value(l, r, lower)`: `lower` 以上で最小の値を返します。存在することを `assert` します。

## 計算量

構築は `O(N log sigma)`、各クエリは `O(log sigma)` です。`sigma` は異なる値の個数です。
