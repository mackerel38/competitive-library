---
title: Rectangle Add Point Get
documentation_of: //structure/rectangle_add_point_get.hpp
---

## 概要

矩形加算と点取得を offline 座標圧縮 2D Fenwick Tree で扱います。
追加される全矩形を先に集め、その 4 隅を構築時に渡します。

## 使い方

```cpp
using DS = poe::rectangle_add_point_get<long long>;
std::vector<DS::rectangle> rects = ...;
DS ds(DS::collect_update_points(rects));
ds.add_rectangle(l, d, r, u, w);
auto x = ds.get(px, py);
```

## 計算量

構築 `O(M log M)`、矩形加算と点取得は `O(log^2 M)` です。`M` は登録した矩形の隅の数です。
