#pragma once

#include "math/number_theory.hpp"
#include "math/prime.hpp"

#include <cmath>
#include <unordered_map>

namespace poe {

long long discrete_log(long long a, long long b, long long mod) {
    assert(mod >= 1);
    a = safe_mod(a, mod);
    b = safe_mod(b, mod);
    if (mod == 1) return 0;
    if (b == 1) return 0;
    long long add = 0, k = 1;
    for (long long g = std::gcd(a, mod); g != 1; g = std::gcd(a, mod)) {
        if (b % g) return -1;
        b /= g;
        mod /= g;
        k = prime_internal::mod_mul(k, a / g, mod);
        ++add;
        if (k == b) return add;
    }
    long long n = static_cast<long long>(std::sqrt(mod) + 1);
    std::unordered_map<long long, long long> table;
    long long e = b;
    for (long long q = 0; q < n; ++q) {
        table[e] = q;
        e = prime_internal::mod_mul(e, a, mod);
    }
    long long an = 1;
    for (long long i = 0; i < n; ++i) an = prime_internal::mod_mul(an, a, mod);
    e = k;
    for (long long p = 1; p <= n + 1; ++p) {
        e = prime_internal::mod_mul(e, an, mod);
        if (auto it = table.find(e); it != table.end()) {
            long long ans = p * n - it->second + add;
            return ans >= 0 ? ans : -1;
        }
    }
    return -1;
}

}  // namespace poe
