---
title: Static Range Count Distinct
documentation_of: //structure/static_range_count_distinct.hpp
---

## 概要

静的配列の区間 `[l, r)` に含まれる異なる値の個数を求めます。
最後の出現位置を永続 segment tree に載せます。

## 使い方

```cpp
poe::static_range_count_distinct<int> ds(a);
int c = ds.prod(l, r);
```

## 計算量

構築 `O(N log N)`、クエリ `O(log N)`、メモリ `O(N log N)` です。
