---
title: DSU
documentation_of: //structure/dsu.hpp
---

## 概要

Disjoint Set Union です。無向グラフの連結成分を併合し、同じ成分か、成分サイズ、成分一覧を取得できます。

## 使い方

```cpp
#include "structure/dsu.hpp"

poe::dsu uf(n);
uf.merge(a, b);
if (uf.same(a, b)) {
    int s = uf.size(a);
}
```

## メソッド

- `dsu(n)`: `n` 頂点で初期化します。
- `merge(a, b)`: `a` と `b` の成分を併合し、併合後の leader を返します。
- `same(a, b)`: 同じ成分なら `true` を返します。
- `leader(a)`: `a` が属する成分の代表元を返します。経路圧縮を行います。
- `size(a)`: `a` が属する成分のサイズを返します。
- `groups()`: 連結成分ごとの頂点列を返します。

## 計算量

`merge`, `same`, `leader`, `size` はならし `O(alpha(N))` です。`groups` は `O(N)` です。
