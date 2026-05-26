---
title: Matrix
documentation_of: //math/matrix.hpp
---

## 概要

テンプレート行列です。整数型や `modint` など、`+`, `-`, `*` が使える型で利用できます。

## 使い方

```cpp
#include "math/matrix.hpp"
#include "math/modint.hpp"

using mint = poe::modint1000000007;

poe::matrix<mint> a(2, 2);
a[0][0] = 1;
a[0][1] = 1;
a[1][0] = 1;

auto b = a.pow(10);
```

## 主な機能

- `matrix(h, w, value)`: `h * w` 行列を作ります。
- `matrix::identity(n)`: `n * n` の単位行列を返します。
- `height()`, `width()`: 行数、列数を返します。
- `operator[]`: 行にアクセスします。
- `+`, `-`, `*`: 行列演算です。
- `pow(n)`: 正方行列の `n` 乗を返します。

## 計算量

行列サイズを `H * W`、乗算相手を `W * K` とします。

- 加算、減算: `O(HW)`
- 乗算: `O(HWK)`
- 累乗: `N * N` 行列で `O(N^3 log e)`

## 注意

サイズが合わない演算は `assert` に失敗します。

このライブラリはまだ verify 未実施です。

