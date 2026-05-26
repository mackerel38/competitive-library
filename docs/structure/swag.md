---
title: SWAG
documentation_of: //structure/swag.hpp
---

## 概要

Sliding Window Aggregation です。キュー全体のモノイド積をならし `O(1)` で管理します。演算は非可換でも使えます。

## メソッド

- `push(x)`: 末尾に追加します。
- `pop()`: 先頭を削除します。
- `fold()`: 現在の全要素の積を返します。
- `front()`, `back()`: 先頭・末尾の値を返します。
- `empty()`, `size()`, `clear()`: 状態を取得・初期化します。

## 計算量

`push`, `pop`, `fold` はならし `O(1)` です。
