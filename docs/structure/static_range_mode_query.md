---
title: Static Range Mode Query
documentation_of: //structure/static_range_mode_query.hpp
---

## 概要

静的配列の区間 `[l, r)` の最頻値と出現回数を求めます。
平方分割でブロック間の候補を前計算し、端の余りを値ごとの出現位置で補います。

## 使い方

```cpp
poe::static_range_mode_query<int> ds(a);
auto [value, count] = ds.prod(l, r);
```

同数の場合に返る値は実装依存です。

## 計算量

構築 `O(N sqrt N)`、クエリ `O(sqrt N log N)` 程度です。
