---
title: KD Tree Rectangle Affine Sum
documentation_of: //structure/kd_tree_rectangle_affine_sum.hpp
---

## 概要

点集合に対して、矩形内の重み総和、矩形内の重みへの一次変換 `w <- a w + b`、点の有効化・点代入を扱います。
全ての追加点を先に渡して構築する offline 型です。

座標分布が片側に集中するケースでは、その座標ごとの lazy segment tree に自動で切り替え、それ以外では KD-tree で処理します。

## 使い方

```cpp
using mint = poe::modint998244353;
std::vector<poe::kd_tree_rectangle_affine_sum<mint>::point> points;
poe::kd_tree_rectangle_affine_sum<mint> ds(points);
ds.apply(l, d, r, u, {a, b});
mint s = ds.sum(l, d, r, u);
ds.set(i, w);
ds.activate(j, w);
```

`activate` は構築時に `active=false` で入れた点を有効化します。

## 計算量

平均的に各操作 `O(sqrt N)` 程度を想定します。片側の座標種類数が小さい場合は、その種類数を `K` として `O(K log N)` です。
