---
title: Li Chao Tree
documentation_of: //structure/li_chao_tree.hpp
---

## 概要

クエリで現れる `x` 座標を先読みして使う Li Chao Tree です。直線追加、線分追加、指定点での最小値取得に対応します。

## 使い方

```cpp
std::vector<long long> xs = {0, 10, 20};
poe::li_chao_tree<long long> cht(xs);
cht.add_line(2, 3);          // y = 2x + 3
cht.add_segment(-1, 5, 0, 10); // [0, 10) 上だけ y = -x + 5
long long ans = cht.get_min(10);
```

## メソッド

- `li_chao_tree(xs)`: 以降 `get_min` する可能性がある `x` 座標を渡して構築します。
- `add_line(a, b)`: 直線 `a x + b` を全域に追加します。
- `add_segment(a, b, l, r)`: 直線 `a x + b` を `x in [l, r)` の範囲に追加します。
- `get_min(x)`: `x` での最小値を返します。`x` は構築時に渡した座標に含まれる必要があります。

## 計算量

`M` を座標数として、各操作は `O(log^2 M)` です。全域直線追加は `O(log M)` です。
