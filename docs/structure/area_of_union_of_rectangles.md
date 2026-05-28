---
title: Area Of Union Of Rectangles
documentation_of: //structure/area_of_union_of_rectangles.hpp
---

## 概要

軸平行長方形の和集合の面積を求めます。座標圧縮した y 座標上の被覆長を持つ sweep line です。

## 使い方

```cpp
poe::area_of_union_of_rectangles<long long> solver;
solver.add_rectangle(l, d, r, u);
auto area = solver.solve();
```

空長方形は無視されます。

## 計算量

長方形数を `N` として `O(N log N)`、メモリ `O(N)` です。
