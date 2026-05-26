---
title: Binary Trie
documentation_of: //structure/binary_trie.hpp
---

## 概要

非負整数集合を二進 Trie で管理します。重複を許し、xor をかけた順序での最小値・最大値・k 番目を取得できます。

## メソッド

- `insert(x, k)`: `x` を `k` 個追加します。
- `erase(x, k)`: `x` を `k` 個削除します。
- `count(x)`, `contains(x)`: 個数・存在判定。
- `kth(k, xor_value)`: `{a xor xor_value}` の昇順で `k` 番目の元の値 `a` を返します。
- `min_element(xor_value)`, `max_element(xor_value)`: xor 後の順序で最小・最大になる元の値を返します。
- `count_less(x, xor_value)`: `a xor xor_value < x` となる個数を返します。
- `count_range(l, r, xor_value)`: `l <= a xor xor_value < r` となる個数を返します。
- `lower_bound(x, xor_value)`: xor 後の値が `x` 以上で最小になる元の値を返します。

## 計算量

各操作は `O(B)` です。`B` は整数型の bit 数です。
