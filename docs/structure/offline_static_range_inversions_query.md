---
title: Offline Static Range Inversions Query
documentation_of: //structure/offline_static_range_inversions_query.hpp
---

## 概要

静的配列に対して、区間 `[l, r)` の転倒数をオフラインで求める構造です。内部で `mo.hpp` と Fenwick Tree を使います。

## メソッド

- `offline_static_range_inversions_query(a)`: 配列 `a` を座標圧縮して構築します。
- `add_query(l, r)`: `[l, r)` の転倒数クエリを追加し、クエリ ID を返します。
- `solve()`: 追加した全クエリの答えを ID 順に返します。

## 計算量

構築は `O(N log N)` です。`Q` 個のクエリに対する `solve()` は、Mo の端点移動回数に Fenwick Tree の `O(log N)` を掛けた時間で動きます。

## 注意

クエリをすべて追加してから `solve()` を呼ぶオフライン構造です。オンラインでの逐次応答はできません。
