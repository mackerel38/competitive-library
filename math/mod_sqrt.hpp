#pragma once

#include "math/number_theory.hpp"
#include "math/prime.hpp"

#include <cassert>

namespace poe {

long long mod_sqrt(long long a, long long p) {
    assert(p > 0);
    a = safe_mod(a, p);
    if (a == 0) return 0;
    if (p == 2) return a;
    if (prime_internal::mod_pow(a, (p - 1) / 2, p) != 1) return -1;
    if (p % 4 == 3) return prime_internal::mod_pow(a, (p + 1) / 4, p);
    long long q = p - 1, s = 0;
    while ((q & 1) == 0) {
        q >>= 1;
        ++s;
    }
    long long z = 2;
    while (prime_internal::mod_pow(z, (p - 1) / 2, p) != static_cast<prime_internal::u64>(p - 1)) ++z;
    long long c = prime_internal::mod_pow(z, q, p);
    long long x = prime_internal::mod_pow(a, (q + 1) / 2, p);
    long long t = prime_internal::mod_pow(a, q, p);
    long long m = s;
    while (t != 1) {
        long long i = 1;
        long long tt = prime_internal::mod_mul(t, t, p);
        while (tt != 1) {
            tt = prime_internal::mod_mul(tt, tt, p);
            ++i;
        }
        long long b = c;
        for (int j = 0; j < m - i - 1; ++j) b = prime_internal::mod_mul(b, b, p);
        x = prime_internal::mod_mul(x, b, p);
        c = prime_internal::mod_mul(b, b, p);
        t = prime_internal::mod_mul(t, c, p);
        m = i;
    }
    return x;
}

}  // namespace poe
