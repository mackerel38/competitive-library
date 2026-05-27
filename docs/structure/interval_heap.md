---
title: Interval Heap
documentation_of: //structure/interval_heap.hpp
---

## 概要

最小値と最大値をどちらも高速に取り出せる double-ended priority queue です。

## メソッド

- `push(x)`: 要素を追加します。
- `min()`, `max()`: 最小値・最大値を参照します。
- `pop_min()`, `pop_max()`: 最小値・最大値を削除して返します。
- `size()`, `empty()`, `reserve(n)`: サイズ、空判定、容量予約です。

## 計算量

`push`, `pop_min`, `pop_max` は `O(log N)`、`min`, `max` は `O(1)` です。
