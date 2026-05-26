---
title: Fenwick Tree
documentation_of: //structure/fenwick_tree.hpp
---

## 概要

Fenwick Tree です。点加算と prefix sum / 区間和を扱えます。`T` は `+`, `-`, `+=`, 比較が必要です。

## 使い方

```cpp
#include "structure/fenwick_tree.hpp"

poe::fenwick_tree<long long> fw(n);
fw.add(i, x);
long long s = fw.sum(l, r);
```

## メソッド

- `fenwick_tree(n)`: 長さ `n` で初期化します。
- `fenwick_tree(v)`: 配列 `v` で初期化します。
- `add(p, x)`: `a[p] += x`。
- `sum(r)`: `[0, r)` の総和を返します。
- `sum(l, r)`, `range_sum(l, r)`: `[l, r)` の総和を返します。
- `all_sum()`: 全体の総和を返します。
- `get(p)`: `a[p]` を返します。
- `set(p, x)`: `a[p] = x`。
- `lower_bound(w)`: prefix sum が初めて `w` 以上になる位置を返します。値が非負であることを仮定します。

## 計算量

各操作は `O(log N)`、`all_sum` は `O(log N)` です。
