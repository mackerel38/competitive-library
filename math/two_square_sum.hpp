#pragma once

#include "math/gaussian_integer.hpp"
#include "math/mod_sqrt.hpp"
#include "math/prime.hpp"

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace poe {

std::pair<long long, long long> prime_two_square(long long p) {
    assert(p == 2 || p % 4 == 1);
    if (p == 2) return {1, 1};
    long long x = mod_sqrt(p - 1, p);
    gaussian_integer g = gaussian_gcd({p, 0}, {x, 1});
    long long a = g.real >= 0 ? g.real : -g.real;
    long long b = g.imag >= 0 ? g.imag : -g.imag;
    if (a > b) std::swap(a, b);
    return {a, b};
}

std::vector<std::pair<long long, long long>> two_square_sum(long long n) {
    assert(n >= 0);
    if (n == 0) return {{0, 0}};
    auto fs = factorize(n);
    for (auto [p, e] : fs) {
        if (p % 4 == 3 && e % 2 == 1) return {};
    }
    gaussian_integer z(1, 0);
    long long mul = 1;
    for (auto [p, e] : fs) {
        if (p == 2) {
            for (int i = 0; i < e; ++i) z *= gaussian_integer(1, 1);
        } else if (p % 4 == 1) {
            auto [a, b] = prime_two_square(p);
            int left = e;
            while (left--) z *= gaussian_integer(a, b);
        } else {
            for (int i = 0; i < e / 2; ++i) mul *= p;
        }
    }
    long long a = std::llabs(z.real) * mul;
    long long b = std::llabs(z.imag) * mul;
    if (a > b) std::swap(a, b);
    return {{a, b}};
}

}  // namespace poe
