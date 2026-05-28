#pragma once

#include "math/prime.hpp"

namespace poe {

namespace tetration_internal {

using i128 = __int128_t;

long long pow_mod_large(long long a, long long e, long long mod) {
    if (mod == 1) return 0;
    long long r = 1 % mod;
    a %= mod;
    while (e) {
        if (e & 1) r = prime_internal::mod_mul(r, a, mod);
        a = prime_internal::mod_mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

bool pow_at_least(long long a, long long e, long long limit) {
    if (limit <= 1) return true;
    if (e == 0) return 1 >= limit;
    i128 res = 1;
    i128 base = a;
    while (e) {
        if (e & 1) {
            res *= base;
            if (res >= limit) return true;
        }
        e >>= 1;
        if (!e) break;
        base *= base;
        if (base >= limit) base = limit;
    }
    return res >= limit;
}

std::pair<long long, bool> tetration_exp(long long a, long long h, long long mod) {
    if (h == 0) return {1 % mod, 1 >= mod};
    if (a == 0) {
        long long v = (h % 2 == 0 ? 1 : 0);
        return {v % mod, v >= mod};
    }
    if (a == 1) return {1 % mod, 1 >= mod};
    if (h == 1) return {a % mod, a >= mod};
    if (mod == 1) return {0, true};
    long long phi = euler_phi(mod);
    auto [e, large] = tetration_exp(a, h - 1, phi);
    long long exponent = e + (large ? phi : 0);
    return {pow_mod_large(a, exponent, mod), pow_at_least(a, exponent, mod)};
}

}  // namespace tetration_internal

long long tetration_mod(long long a, long long height, long long mod) {
    assert(height >= 0 && mod >= 1);
    if (height == 0) return 1 % mod;
    return tetration_internal::tetration_exp(a, height, mod).first;
}

}  // namespace poe
