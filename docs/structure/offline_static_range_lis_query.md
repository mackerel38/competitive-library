---
title: Offline Static Range LIS Query
documentation_of: //structure/offline_static_range_lis_query.hpp
---

## 概要

順列 `p` の区間 `[l, r)` に含まれる最長増加部分列の長さを offline で求めます。
seaweed matrix を作り、各クエリを 2 次元 offline count に変換します。

## 使い方

```cpp
poe::offline_static_range_lis_query ds(p);
int id = ds.add_query(l, r);
auto ans = ds.solve();
```

`ans[id]` にクエリの答えが入ります。入力配列は `0..N-1` の順列を想定します。

## 計算量

`N` を配列長、`Q` をクエリ数として、構築と回答は `O(N log^2 N + (N + Q) log N)`、メモリ `O(N + Q)` です。
