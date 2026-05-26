#pragma once

#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

namespace poe {

constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

constexpr long long pow_mod(long long x, long long n, int mod) {
    assert(n >= 0);
    assert(mod >= 1);
    if (mod == 1) return 0;
    long long r = 1 % mod;
    x = safe_mod(x, mod);
    while (n) {
        if (n & 1) r = r * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return r;
}

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;
    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

constexpr long long mod_inv(long long a, long long mod) {
    auto [g, x] = inv_gcd(a, mod);
    assert(g == 1);
    return x;
}

std::pair<long long, long long> crt(const std::vector<long long>& r, const std::vector<long long>& m) {
    assert(r.size() == m.size());
    long long r0 = 0, m0 = 1;
    for (int i = 0; i < static_cast<int>(r.size()); ++i) {
        assert(m[i] >= 1);
        long long r1 = safe_mod(r[i], m[i]), m1 = m[i];
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        auto [g, im] = inv_gcd(m0, m1);
        long long u1 = m1 / g;
        if ((r1 - r0) % g) return {0, 0};
        long long x = (r1 - r0) / g % u1 * im % u1;
        r0 += x * m0;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}

long long floor_sum(long long n, long long m, long long a, long long b) {
    assert(0 <= n && 1 <= m);
    long long ans = 0;
    if (a < 0) {
        long long a2 = safe_mod(a, m);
        ans -= n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        long long b2 = safe_mod(b, m);
        ans -= n * ((b2 - b) / m);
        b = b2;
    }
    while (true) {
        if (a >= m) {
            ans += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        long long y_max = a * n + b;
        if (y_max < m) break;
        n = y_max / m;
        b = y_max % m;
        std::swap(m, a);
    }
    return ans;
}

}  // namespace poe

