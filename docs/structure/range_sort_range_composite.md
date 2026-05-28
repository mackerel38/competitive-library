---
title: Range Sort Range Composite
documentation_of: //structure/range_sort_range_composite.hpp
---

## 概要

要素 `(p, a, b)` を持つ列に対して、点更新、`p` による区間昇順/降順ソート、区間の一次関数合成を行います。
列をソート済みブロックに分解し、各ブロックを `p` キーの動的 segment tree、ブロック積を通常の segment tree で管理します。

## 使い方

```cpp
using mint = poe::modint998244353;
std::vector<poe::range_sort_range_composite<mint>::item> a;
poe::range_sort_range_composite<mint> ds(a);
ds.set(i, {p, c, d});
ds.sort_ascending(l, r);
ds.sort_descending(l, r);
auto f = ds.prod(l, r); // f(x) = f.a * x + f.b
```

合成は左から右へ関数列を適用する順序です。

## 計算量

全体でならし `O((N + Q) log P)` 程度です。`P` は `p` の値域です。
