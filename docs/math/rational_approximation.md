---
title: Rational Approximation
documentation_of: //math/rational_approximation.hpp
---

## 概要

有理数型と、有理数近似の補助を提供します。

## 使い方

```cpp
#include "math/rational_approximation.hpp"

poe::rational x(p, q);
auto best = poe::best_rational_approximation(p, q, max_den);
```

## 計算量

`best_rational_approximation` は `O(max_den)` です。

