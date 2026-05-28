---
title: Static Rectangle Add Rectangle Sum
documentation_of: //structure/static_rectangle_add_rectangle_sum.hpp
---

## 概要

重み付き矩形をすべて先に追加し、クエリ矩形内の総和を offline で求めます。
矩形加算を 4 つの符号付きイベントに分解し、x sweep と Fenwick Tree で処理します。

## 使い方

```cpp
poe::static_rectangle_add_rectangle_sum<long long> solver;
solver.add_rectangle(l, d, r, u, w);
int id = solver.add_query(l, d, r, u);
auto ans = solver.solve();
```

`ans[id]` が対応するクエリの答えです。

## 計算量

矩形数を `N`、クエリ数を `Q` として `O((N + Q) log (N + Q))`、メモリ `O(N + Q)` です。
