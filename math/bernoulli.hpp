#pragma once

#include "math/modint.hpp"

#include <vector>

namespace poe {

template <class Mint>
std::vector<Mint> bernoulli_numbers(int n) {
    std::vector<Mint> a(n + 1), b(n + 1);
    for (int m = 0; m <= n; ++m) {
        a[m] = Mint(1) / Mint(m + 1);
        for (int j = m; j >= 1; --j) a[j - 1] = Mint(j) * (a[j - 1] - a[j]);
        b[m] = a[0];
    }
    return b;
}

}  // namespace poe

