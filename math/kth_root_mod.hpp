#pragma once

#include "math/number_theory.hpp"
#include "math/prime.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace poe {

namespace kth_root_mod_internal {

using i64 = long long;

i64 mul_mod(i64 a, i64 b, i64 mod) {
    return static_cast<i64>(prime_internal::mod_mul(static_cast<prime_internal::u64>(a), static_cast<prime_internal::u64>(b),
                                                    static_cast<prime_internal::u64>(mod)));
}

i64 pow_mod_u64(i64 a, i64 n, i64 mod) {
    return static_cast<i64>(prime_internal::mod_pow(static_cast<prime_internal::u64>(safe_mod(a, mod)),
                                                    static_cast<prime_internal::u64>(n),
                                                    static_cast<prime_internal::u64>(mod)));
}

i64 inv_prime(i64 a, i64 p) { return pow_mod_u64(a, p - 2, p); }

struct fast_bsgs {
    i64 mod;
    int size;
    int mask;
    int period;
    i64 gpow;
    std::vector<std::pair<i64, int>> values;
    std::vector<int> offset;

    fast_bsgs(i64 g, int s, int period_, i64 mod_) : mod(mod_), period(period_) {
        int lim = std::max(1, std::min(s, period));
        size = 1;
        while ((size << 1) <= lim) size <<= 1;
        mask = size - 1;
        values.resize(size);
        offset.assign(size + 1, 0);

        i64 x = 1 % mod;
        for (int i = 0; i < size; ++i) {
            ++offset[x & mask];
            x = mul_mod(x, g, mod);
        }
        for (int i = 1; i < size; ++i) offset[i] += offset[i - 1];
        x = 1 % mod;
        for (int i = 0; i < size; ++i) {
            values[--offset[x & mask]] = {x, i};
            x = mul_mod(x, g, mod);
        }
        gpow = x;
        offset[size] = size;
    }

    int find(i64 x) const {
        for (int t = 0; t < period; t += size) {
            int bucket = x & mask;
            for (int i = offset[bucket]; i < offset[bucket + 1]; ++i) {
                if (values[i].first == x) {
                    int ret = values[i].second - t;
                    return ret < 0 ? ret + period : ret;
                }
            }
            x = mul_mod(x, gpow, mod);
        }
        return -1;
    }
};

i64 prime_power_root(i64 c, i64 pi, int ei, i64 p) {
    i64 s = p - 1;
    int t = 0;
    while (s % pi == 0) {
        s /= pi;
        ++t;
    }
    i64 pe = 1;
    for (int i = 0; i < ei; ++i) pe *= pi;

    i64 u = mod_inv(pe - s % pe, pe);
    i64 z = pow_mod_u64(c, (s * u + 1) / pe, p);
    i64 zpe = pow_mod_u64(c, s * u, p);
    if (zpe == 1) return z;

    i64 ptm1 = 1;
    for (int i = 0; i < t - 1; ++i) ptm1 *= pi;
    i64 vs = 1;
    for (i64 v = 2;; ++v) {
        vs = pow_mod_u64(v, s, p);
        if (pow_mod_u64(vs, ptm1, p) != 1) break;
    }

    i64 vspe = pow_mod_u64(vs, pe, p);
    int vs_e = ei;
    i64 base = vspe;
    for (int i = 0; i < t - ei - 1; ++i) base = pow_mod_u64(base, pi, p);
    int bsgs_size = static_cast<int>(std::sqrt(static_cast<long double>(std::max(1, t - ei))) *
                                     std::sqrt(static_cast<long double>(pi))) +
                    1;
    fast_bsgs memo(base, bsgs_size, static_cast<int>(pi), p);

    while (zpe != 1) {
        i64 tmp = zpe;
        int td = 0;
        while (tmp != 1) {
            ++td;
            tmp = pow_mod_u64(tmp, pi, p);
        }
        int e = t - td;
        while (vs_e != e) {
            vs = pow_mod_u64(vs, pi, p);
            vspe = pow_mod_u64(vspe, pi, p);
            ++vs_e;
        }

        i64 target = inv_prime(zpe, p);
        for (int i = 0; i < td - 1; ++i) target = pow_mod_u64(target, pi, p);
        int bsgs = memo.find(target);
        assert(bsgs >= 0);
        z = mul_mod(z, pow_mod_u64(vs, bsgs, p), p);
        zpe = mul_mod(zpe, pow_mod_u64(vspe, bsgs, p), p);
    }
    return z;
}

}  // namespace kth_root_mod_internal

long long kth_root_mod(long long a, long long k, long long p) {
    using namespace kth_root_mod_internal;
    assert(k >= 0 && p >= 2 && is_prime(p));
    a = safe_mod(a, p);
    if (k == 0) return a == 1 ? 1 : -1;
    if (a <= 1 || k <= 1) return a;
    if (p == 2) return a;

    long long g = std::gcd(k, p - 1);
    if (pow_mod_u64(a, (p - 1) / g, p) != 1) return -1;
    a = pow_mod_u64(a, mod_inv(safe_mod(k / g, (p - 1) / g), (p - 1) / g), p);

    std::unordered_map<long long, int> fac;
    for (auto [q, e] : factorize(g)) fac[q] += e;
    for (auto [q, e] : fac) a = prime_power_root(a, q, e, p);
    return a;
}

class prime_mod_kth_root_solver {
public:
    explicit prime_mod_kth_root_solver(long long p) : p_(p) { assert(p_ >= 2 && is_prime(p_)); }
    long long kth_root(long long a, long long k) const { return kth_root_mod(a, k, p_); }

private:
    long long p_;
};

}  // namespace poe
