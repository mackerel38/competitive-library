---
title: Formal Power Series
documentation_of: //math/fps.hpp
---

## 概要

形式的冪級数です。`math/convolution.hpp` に依存し、畳み込みは NTT を使います。

## 使い方

```cpp
#include "math/fps.hpp"

using mint = poe::modint998244353;
using fps = poe::formal_power_series<mint>;

fps f = {1, 1, 1};
auto g = f.inv(10);
```

## 主な機能

- `pre(n)`: 先頭 `n` 項を返します。
- `rev()`: 係数を反転した列を返します。
- `shrink()`: 末尾の 0 を削除します。
- `diff()`: 微分を返します。
- `integral()`: 積分を返します。
- `inv(deg)`: 逆数を `deg` 項まで返します。
- `log(deg)`: 対数を `deg` 項まで返します。
- `exp(deg)`: 指数を `deg` 項まで返します。
- `pow(k, deg)`: `k` 乗を `deg` 項まで返します。

## 計算量

必要項数を `N` とします。

- 加算、減算、微分、積分: `O(N)`
- 乗算: `O(N log N)`
- `inv`, `log`: `O(N log N)`
- `exp`, `pow`: 現在の実装では `O(N^2)`

## 注意

`inv` は定数項が 0 でないこと、`log` は定数項が 1 であること、`exp` は定数項が 0 であることを仮定します。

このライブラリはまだ verify 未実施です。
