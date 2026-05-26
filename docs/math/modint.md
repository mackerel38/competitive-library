---
title: Modint
documentation_of: //math/modint.hpp
---

## 概要

剰余付き整数型です。`static_modint<MOD>`、`dynamic_modint<ID>`、代表的な alias として `modint998244353`、`modint1000000007`、`modint` を提供します。

階乗前計算用の `mod_combination<Mint>` もこのヘッダに含みます。

## 使い方

```cpp
#include "math/modint.hpp"

using mint = poe::modint998244353;

mint a = 10;
mint b = 3;
mint c = a / b;

poe::mod_combination<mint> comb(1000000);
mint ans = comb.C(10, 3);
```

動的 mod は先に `set_mod` を呼びます。

```cpp
using mint = poe::modint;
mint::set_mod(1000000007);
```

## 主な機能

- `Mint::mod()`: mod を返します。
- `Mint::raw(x)`: `0 <= x < mod` を仮定して値を作ります。
- `val()`: 現在の値を `int` で返します。
- `pow(n)`: `n` 乗を返します。
- `inv()`: 逆元を返します。存在しない場合は `assert` に失敗します。
- `mod_combination<Mint>::C(n, k)`: 組合せを返します。
- `mod_combination<Mint>::P(n, k)`: 順列を返します。
- `mod_combination<Mint>::H(n, k)`: 重複組合せを返します。

## 計算量

- 四則演算: `O(1)`
- `pow(n)`: `O(log n)`
- `inv()`: `O(log mod)`
- `mod_combination::reserve(n)`: 追加分を `N` として `O(N)`
- `C(n, k)`, `P(n, k)`, `H(n, k)`: 前計算済みなら `O(1)`

## 注意

`mod_combination` は階乗の逆元を使うため、必要な階乗値が mod と互いに素であることを仮定します。典型的には素数 mod で使います。

`modint998244353` の基本演算は `convolution_mod` の verify で確認しています。`mod_combination` はまだ個別 verify 未実施です。
