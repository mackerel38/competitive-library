---
title: Simple Treap
documentation_of: //structure/simple_treap.hpp
---

## 概要

他のライブラリの内部部品として使いやすい、薄い implicit Treap です。列を表す木を `split` / `merge` でき、点の挿入・削除・取得・代入ができます。モノイド集約や遅延伝播は `treap.hpp` を使います。

## 使い方

```cpp
#include "structure/simple_treap.hpp"

poe::simple_treap<int> tr({1, 2, 3});
tr.insert(1, 10);      // 1, 10, 2, 3
auto right = tr.split_off(2);
tr.merge_back(right);
```

## メソッド

- `simple_treap(v)`: 配列 `v` から構築します。
- `make_node(x)`: 値 `x` のノードを作ります。
- `merge(l, r)`: 2 つの木を結合します。すべての `l` の要素が `r` より前にあることを仮定します。
- `split(t, k)`: 木 `t` を `[0, k)` と `[k, n)` に分けます。
- `insert(p, x)`: 位置 `p` に `x` を挿入します。
- `erase(p)`: 位置 `p` を削除し、削除した値を返します。
- `get(p)`, `kth(k)`: 位置 `p` / `k` の値を返します。
- `set(p, x)`: 位置 `p` を `x` にします。
- `lower_bound(x)`: 列が昇順にソートされているとき、`x` 以上の最初の位置を返します。
- `upper_bound(x)`: 列が昇順にソートされているとき、`x` より大きい最初の位置を返します。
- `count_lt(x)`, `count_le(x)`, `count_ge(x)`, `count_gt(x)`: ソート済み列で `x` 未満、以下、以上、より大きい個数を返します。
- `contains_sorted(x)`: ソート済み列に `x` が含まれるかを返します。
- `split_off(k)`: 自分を `[0, k)` にし、`[k, n)` を新しい `simple_treap` として返します。
- `merge_back(other)`: `other` を末尾に結合します。
- `to_vector()`: 現在の列を返します。

## 計算量

構築は `O(N log N)`、各操作は期待 `O(log N)` です。

## 注意

`split_off` で分けた木は内部のノード管理領域を共有します。コンテスト中に値として持ち回る用途を想定しています。

値ベースの二分探索系メソッドは、inorder の列が比較関数に対してソート済みであることを仮定します。通常の `insert(p, x)` で任意位置に挿入した列に対しては、順序が保たれている場合だけ使えます。

## Verify

直接対応する公開問題がないため、`verify/simple_treap_random.test.cpp` で `std::vector` との乱択比較を行います。
