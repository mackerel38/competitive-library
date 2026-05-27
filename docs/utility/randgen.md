---
title: Randgen
documentation_of: //utility/randgen.hpp
---

## 概要

競技プログラミング向けの高速な乱数生成器です。`splitmix64` を使い、Treap の priority、乱択アルゴリズム、テスト生成、shuffle などで使えます。

暗号学的に安全な乱数ではありません。ここでの「安全」は、固定 seed の `rand()` や単純な `mt19937` より hack されにくく、偏りが少なく、競技用途で扱いやすいという意味です。

## 使い方

```cpp
#include "utility/randgen.hpp"

poe::random_engine rng;
unsigned long long x = rng();
int a = rng.uniform_int(0, 10);  // [0, 10)
rng.shuffle(v.begin(), v.end());
```

## 主な機能

- `random_engine()`: 時刻、アドレス、`std::random_device` を混ぜて seed を作ります。
- `random_engine(seed)`: 指定 seed で初期化します。
- `operator()()`: `uint64_t` の乱数を返します。
- `uniform_u64(l, r)`: `[l, r)` の `uint64_t` を返します。`l < r` が必要です。
- `uniform_int(l, r)`: `[l, r)` の `int` を返します。
- `uniform_ll(l, r)`: `[l, r)` の `long long` を返します。
- `uniform_real()`: `[0, 1)` の `double` を返します。
- `shuffle(first, last)`: 範囲を Fisher-Yates shuffle します。
- `global_random_engine()`: グローバルな乱数生成器への参照を返します。
- `rand_u64()`, `rand_int(l, r)`, `rand_ll(l, r)`: グローバル生成器を使う簡易関数です。

## 計算量

各乱数生成は期待 `O(1)`、`shuffle` は要素数を `N` として `O(N)` です。

## Verify

乱数生成器そのものに対応する公開 judge 問題はないため、`structure/treap.hpp` と `structure/simple_treap.hpp` の verify で `utility/randgen.hpp` を include して使用しています。
