---
title: Foldable Deque
documentation_of: //structure/foldable_deque.hpp
---

## 概要

両端 push/pop と全体のモノイド積を扱う deque です。非可換モノイドにも対応します。

## メソッド

- `push_front(x)`, `push_back(x)`: 両端に要素を追加します。
- `pop_front()`, `pop_back()`: 両端から要素を削除します。空でないことを `assert` します。
- `fold()`: 現在の列を前から順に畳み込んだ値を返します。
- `size()`, `empty()`: 要素数と空判定です。

## 計算量

各操作はならし `O(1)` です。
