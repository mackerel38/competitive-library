---
title: Prime
documentation_of: //math/prime.hpp
---

## 概要

素数系の処理をまとめたヘッダです。素数判定、篩、線形篩、素因数分解、約数列挙を提供します。

## 使い方

```cpp
#include "math/prime.hpp"

bool ok = poe::is_prime(1000000007);
auto factors = poe::factorize(600851475143LL);
auto ds = poe::divisors(360);

poe::linear_sieve ls(1000000);
auto small = ls.factorize(840);
```

## 主な機能

- `is_prime(n)`: Miller-Rabin による `long long` 向け素数判定です。
- `sieve(n)`: `n` 以下の素数列を返します。
- `linear_sieve(n)`: 最小素因数と素数列を前計算します。
- `linear_sieve::factorize(x)`: `x <= n` の素因数分解を返します。
- `factorize(n)`: Pollard Rho による `long long` の素因数分解を返します。
- `divisors(n)`: 正の約数を昇順で返します。

## 計算量

- `sieve(n)`: `O(n log log n)`
- `linear_sieve(n)`: `O(n)`
- `linear_sieve::factorize(x)`: 素因数の個数を `K` として `O(K)`
- `is_prime(n)`: `O(log n)` 程度
- `factorize(n)`: 期待的に高速です。Pollard Rho の性質上、入力に依存します。
- `divisors(n)`: 約数の個数を `D` として `O(D log D)`

## 注意

`factorize` と `divisors` は `n >= 1` を仮定します。

`is_prime` は `primality_test`、`factorize` は `factorize` で verify 済みです。`sieve`、`linear_sieve`、`divisors` はまだ個別 verify 未実施です。
