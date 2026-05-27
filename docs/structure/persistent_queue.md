---
title: Persistent Queue
documentation_of: //structure/persistent_queue.hpp
---

## 概要

永続キューです。`push` と `pop` は新しいキューを返し、元のキューは変更しません。各要素は親ポインタと doubling を持つノードとして共有されます。

## メソッド

- `push(x)`: 末尾に `x` を追加した新しいキューを返します。
- `pop()`: 先頭を削除した新しいキューを返します。空でないことを `assert` します。
- `front()`: 先頭の値を返します。空でないことを `assert` します。
- `back()`: 末尾の値を返します。空でないことを `assert` します。
- `size()`: 要素数を返します。
- `empty()`: 空かどうかを返します。

## 計算量

`push` は `O(log N)`、`pop` は `O(1)`、`front` は `O(log N)` です。`N` はそのバージョンまでに積まれた要素数です。
