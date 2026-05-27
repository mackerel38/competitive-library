---
title: Treap
documentation_of: //structure/treap.hpp
---

## 概要

遅延伝播と反転に対応した implicit Treap です。列に対して挿入、削除、区間積、区間作用、区間反転、split、merge を扱えます。`lazy_segtree` と同じ形で、モノイド `S`、作用 `F`、`op`, `e`, `mapping`, `composition`, `id` を渡します。

## 使い方

```cpp
#include "structure/treap.hpp"

poe::treap<S, op, e, F, mapping, composition, id> tr(v);
tr.insert(pos, x);
tr.apply(l, r, f);
tr.reverse(l, r);
S ans = tr.prod(l, r);
```

## メソッド

- `treap(v)`: 配列 `v` から構築します。
- `make_node(x)`: 値 `x` のノードを作ります。
- `merge(l, r)`: 2 つの木を結合します。
- `split(t, k)`: 木 `t` を `[0, k)` と `[k, n)` に分けます。
- `insert(p, x)`: 位置 `p` に `x` を挿入します。
- `erase(p)`: 位置 `p` を削除し、削除した値を返します。
- `get(p)`, `kth(k)`, `set(p, x)`: 点取得・k 番目取得・点代入。
- `prod(l, r)`: `[l, r)` のモノイド積を返します。
- `all_prod()`: 全体のモノイド積を返します。
- `max_right(l, g)`: `g(prod(l, r))` が成り立つ最大の `r` を返します。
- `min_left(r, g)`: `g(prod(l, r))` が成り立つ最小の `l` を返します。
- `apply(p, f)`, `apply(l, r, f)`: 点または区間に作用を適用します。
- `reverse(l, r)`: `[l, r)` を反転します。
- `rotate(l, m, r)`: `[l, m)` と `[m, r)` を入れ替えます。
- `split_off(k)`: 自分を `[0, k)` にし、`[k, n)` を新しい `treap` として返します。
- `merge_back(other)`: `other` を末尾に結合します。
- `to_vector()`: 現在の列を返します。

## 計算量

構築は `O(N log N)`、各操作は期待 `O(log N)` です。`to_vector` は `O(N)` です。

## 注意

反転に対応するため、内部では正順の積と逆順の積を両方持ちます。非可換モノイドでも `reverse` 後の `prod` が正しく動くようにしています。

`split_off` で分けた木は内部のノード管理領域を共有します。木同士の `merge` は、同じ `treap` から分割した木や、このライブラリで作った木に対して使う想定です。
