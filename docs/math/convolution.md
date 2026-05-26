---
title: Convolution
documentation_of: //math/convolution.hpp
---

## 概要

NTT による畳み込みです。`math/modint.hpp` の `static_modint` を使います。任意 mod の畳み込みも提供します。

## 使い方

```cpp
#include "math/convolution.hpp"

using mint = poe::modint998244353;

std::vector<mint> a = {1, 2, 3};
std::vector<mint> b = {4, 5};
auto c = poe::convolution(a, b);

auto d = poe::convolution_mod({1, 2, 3}, {4, 5}, 1000000007);
```

## 主な機能

- `convolution<Mint>(a, b)`: `Mint` 上の畳み込みを返します。
- `convolution_mod(a, b, mod)`: 任意 mod での畳み込みを返します。
- `convolution_ll(a, b)`: 64 bit 整数の畳み込みを返します。結果が `long long` に収まることを仮定します。

## 計算量

畳み込み後の長さを `N` として `O(N log N)` です。

## 注意

`convolution<Mint>` は NTT 可能な素数 mod を仮定します。代表例は `998244353` です。

`convolution<modint998244353>` は `convolution_mod` で verify 済みです。`convolution_mod` と `convolution_ll` はまだ個別 verify 未実施です。
