#pragma once

#include "math/modint.hpp"

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>

namespace poe {

namespace internal {

constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 880803841) return 26;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (long long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = static_cast<int>(i);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int g = 2;; ++g) {
        bool ok = true;
        for (int i = 0; i < cnt; ++i) {
            long long e = (m - 1) / divs[i];
            long long v = 1, y = g;
            while (e) {
                if (e & 1) v = v * y % m;
                y = y * y % m;
                e >>= 1;
            }
            if (v == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

template <class Mint>
void ntt(std::vector<Mint>& a, bool inverse) {
    int n = static_cast<int>(a.size());
    assert((n & (n - 1)) == 0);
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    Mint g = primitive_root_constexpr(Mint::mod());
    for (int len = 2; len <= n; len <<= 1) {
        Mint wlen = g.pow((Mint::mod() - 1) / len);
        if (inverse) wlen = wlen.inv();
        for (int i = 0; i < n; i += len) {
            Mint w = 1;
            for (int j = 0; j < len / 2; ++j) {
                Mint u = a[i + j];
                Mint v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inverse) {
        Mint inv_n = Mint(n).inv();
        for (auto& x : a) x *= inv_n;
    }
}

}  // namespace internal

template <class Mint>
std::vector<Mint> convolution(std::vector<Mint> a, std::vector<Mint> b) {
    if (a.empty() || b.empty()) return {};
    int need = static_cast<int>(a.size() + b.size() - 1);
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    internal::ntt(a, false);
    internal::ntt(b, false);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    internal::ntt(a, true);
    a.resize(need);
    return a;
}

std::vector<long long> convolution_mod(const std::vector<long long>& a, const std::vector<long long>& b, long long mod) {
    assert(mod >= 1);
    if (a.empty() || b.empty()) return {};
    using m1 = static_modint<167772161>;
    using m2 = static_modint<469762049>;
    using m3 = static_modint<754974721>;
    std::vector<m1> a1(a.begin(), a.end()), b1(b.begin(), b.end());
    std::vector<m2> a2(a.begin(), a.end()), b2(b.begin(), b.end());
    std::vector<m3> a3(a.begin(), a.end()), b3(b.begin(), b.end());
    auto c1 = convolution(a1, b1);
    auto c2 = convolution(a2, b2);
    auto c3 = convolution(a3, b3);
    const long long mod1 = m1::mod();
    const long long mod2 = m2::mod();
    const long long mod3 = m3::mod();
    const long long inv_m1_mod2 = m2(mod1).inv().val();
    const long long inv_m1m2_mod3 = m3(static_cast<long long>((static_cast<__int128>(mod1) * mod2) % mod3)).inv().val();
    std::vector<long long> res(c1.size());
    for (int i = 0; i < static_cast<int>(c1.size()); ++i) {
        long long x1 = c1[i].val();
        long long x2 = (c2[i].val() - x1) * inv_m1_mod2 % mod2;
        if (x2 < 0) x2 += mod2;
        long long x3 = (c3[i].val() - (x1 + static_cast<__int128>(mod1) * x2) % mod3) * inv_m1m2_mod3 % mod3;
        if (x3 < 0) x3 += mod3;
        __int128 x = x1 + static_cast<__int128>(mod1) * x2 + static_cast<__int128>(mod1) * mod2 * x3;
        res[i] = static_cast<long long>(x % mod);
    }
    return res;
}

std::vector<long long> convolution_ll(const std::vector<long long>& a, const std::vector<long long>& b) {
    if (a.empty() || b.empty()) return {};
    using m1 = static_modint<167772161>;
    using m2 = static_modint<469762049>;
    using m3 = static_modint<754974721>;
    std::vector<m1> a1(a.begin(), a.end()), b1(b.begin(), b.end());
    std::vector<m2> a2(a.begin(), a.end()), b2(b.begin(), b.end());
    std::vector<m3> a3(a.begin(), a.end()), b3(b.begin(), b.end());
    auto c1 = convolution(a1, b1);
    auto c2 = convolution(a2, b2);
    auto c3 = convolution(a3, b3);
    const long long mod1 = m1::mod();
    const long long mod2 = m2::mod();
    const long long mod3 = m3::mod();
    const long long inv_m1_mod2 = m2(mod1).inv().val();
    const long long inv_m1m2_mod3 = m3(static_cast<long long>((static_cast<__int128>(mod1) * mod2) % mod3)).inv().val();
    std::vector<long long> res(c1.size());
    for (int i = 0; i < static_cast<int>(c1.size()); ++i) {
        long long x1 = c1[i].val();
        long long x2 = (c2[i].val() - x1) * inv_m1_mod2 % mod2;
        if (x2 < 0) x2 += mod2;
        long long x3 = (c3[i].val() - (x1 + static_cast<__int128>(mod1) * x2) % mod3) * inv_m1m2_mod3 % mod3;
        if (x3 < 0) x3 += mod3;
        res[i] = static_cast<long long>(x1 + static_cast<__int128>(mod1) * x2 + static_cast<__int128>(mod1) * mod2 * x3);
    }
    return res;
}

}  // namespace poe
