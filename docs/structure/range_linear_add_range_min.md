---
title: Range Linear Add Range Min
documentation_of: //structure/range_linear_add_range_min.hpp
---

## 概要

配列 `a` に対して、区間 `[l, r)` の各 `i` に `b*i+c` を加算し、区間最小値を取得します。
平方分割と各ブロックの下側凸包で処理します。

## 使い方

```cpp
poe::range_linear_add_range_min<long long> ds(a);
ds.apply(l, r, b, c);
auto mn = ds.prod(l, r);
```

## 計算量

配列長を `N` として、各操作はおおよそ `O(sqrt N log N)` です。
