---
title: Number Theory
documentation_of: //math/number_theory.hpp
---

## 概要

素数判定や素因数分解以外の整数論補助です。mod 演算、逆元、中国剰余定理、floor sum を提供します。

## 使い方

```cpp
#include "math/number_theory.hpp"

auto [r, m] = poe::crt({2, 3}, {5, 7});
long long s = poe::floor_sum(n, m, a, b);
```

## 主な機能

- `safe_mod(x, m)`: `x mod m` を `0 <= r < m` に正規化します。
- `pow_mod(x, n, mod)`: `x^n mod mod` を返します。
- `inv_gcd(a, b)`: `gcd(a, b)` と `a` の逆元に対応する値を返します。
- `mod_inv(a, mod)`: `a` の mod 逆元を返します。
- `crt(r, m)`: `x = r[i] mod m[i]` を満たす最小非負解と lcm を返します。解なしなら `{0, 0}` です。
- `floor_sum(n, m, a, b)`: `sum_{0 <= i < n} floor((a * i + b) / m)` を返します。

## 計算量

- `pow_mod`: `O(log n)`
- `mod_inv`: `O(log mod)`
- `crt`: 式の本数を `K` として `O(K log lcm(m))`
- `floor_sum`: `O(log m + log a)`

## 注意

`mod_inv` は逆元が存在することを仮定し、存在しない場合は `assert` に失敗します。

`floor_sum` は `sum_of_floor_of_linear` で verify 済みです。`crt` や `mod_inv` はまだ個別 verify 未実施です。
