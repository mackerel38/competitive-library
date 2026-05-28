---
title: Mo
documentation_of: //structure/mo.hpp
---

## 概要

静的配列上の区間クエリをオフラインで並べ替えて処理する Mo's algorithm です。現在の区間を `[l, r)` として保ち、端点を 1 つずつ動かすための関数を渡して使います。

既定では Hilbert order でクエリを並べます。単純なブロック順より移動量が安定しやすく、偏った入力でも崩れにくい順序です。必要なら `order_type::block` で奇偶ブロック順も使えます。

## 使い方

```cpp
poe::mo mo(n);
for (auto [l, r] : queries) mo.add_query(l, r);

mo.run(
    [&](int i) { add_left(i); },
    [&](int i) { add_right(i); },
    [&](int i) { erase_left(i); },
    [&](int i) { erase_right(i); },
    [&](int id) { ans[id] = current_answer; }
);
```

左右で追加・削除の処理が同じ場合は短く書けます。

```cpp
mo.run(
    [&](int i) { add(i); },
    [&](int i) { erase(i); },
    [&](int id) { ans[id] = current_answer; }
);
```

`answer` は `answer(id)` だけでなく、`answer(id, l, r)` も受け取れます。

## メソッド

- `mo(n, order)`: 長さ `n` の列に対する Mo を作ります。`order` は省略すると `order_type::hilbert` です。
- `add_query(l, r)`: `[l, r)` のクエリを追加し、そのクエリ ID を返します。
- `size()`: 追加済みクエリ数を返します。
- `queries()`: 追加したクエリ列を返します。
- `ordered_queries()`: Mo 順に並べ替えたクエリ列を返します。
- `run(add_left, add_right, erase_left, erase_right, answer)`: 現在区間を動かしながら各クエリの `answer` を呼びます。
- `run(add, erase, answer)`: 左右の追加・削除が同じ場合の省略形です。

## 計算量

`Q` 個のクエリに対して、並べ替えは `O(Q log Q)` です。実行時間は区間端点の移動回数に、渡した追加・削除関数の計算量を掛けたものです。

## 注意

`run` はクエリを入力順ではなく Mo 順に処理します。答えは `id` を使って元の順番に保存してください。
