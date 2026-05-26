---
title: Hashmap
documentation_of: //structure/hashmap.hpp
---

## 概要

`splitmix64` を使う `custom_hash` と、それを使う `hashmap`, `hashset` の alias です。整数キーや pair キーで使いやすいようにしています。

## 使い方

```cpp
#include "structure/hashmap.hpp"

poe::hashmap<long long, int> mp;
poe::hashset<std::pair<int, int>> st;
```

## 内容

- `custom_hash`: 整数と `std::pair` に対応した hash 関数です。
- `hashmap<Key, T>`: `std::unordered_map<Key, T, custom_hash>`。
- `hashset<Key>`: `std::unordered_set<Key, custom_hash>`。

## 計算量

期待 `O(1)` です。
