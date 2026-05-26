#pragma once

#include <cassert>
#include <iostream>
#include <limits>
#include <type_traits>
#include <vector>

namespace poe {

namespace internal {

constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
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

}  // namespace internal

template <int MOD>
class static_modint {
    static_assert(MOD > 0);

public:
    using mint = static_modint;

    static constexpr int mod() { return MOD; }

    constexpr static_modint() : v_(0) {}

    template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    constexpr static_modint(T v) : v_(static_cast<unsigned int>(internal::safe_mod(static_cast<long long>(v), MOD))) {}

    static constexpr mint raw(int v) {
        mint x;
        x.v_ = static_cast<unsigned int>(v);
        return x;
    }

    constexpr int val() const { return static_cast<int>(v_); }

    constexpr mint operator+() const { return *this; }
    constexpr mint operator-() const { return v_ == 0 ? mint() : raw(MOD - static_cast<int>(v_)); }

    constexpr mint& operator+=(const mint& rhs) {
        v_ += rhs.v_;
        if (v_ >= MOD) v_ -= MOD;
        return *this;
    }

    constexpr mint& operator-=(const mint& rhs) {
        if (v_ < rhs.v_) v_ += MOD;
        v_ -= rhs.v_;
        return *this;
    }

    constexpr mint& operator*=(const mint& rhs) {
        v_ = static_cast<unsigned int>((static_cast<unsigned long long>(v_) * rhs.v_) % MOD);
        return *this;
    }

    constexpr mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

    constexpr mint pow(long long n) const {
        assert(n >= 0);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }

    constexpr mint inv() const {
        auto [g, x] = internal::inv_gcd(v_, MOD);
        assert(g == 1);
        return x;
    }

    friend constexpr mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    friend constexpr mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    friend constexpr mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    friend constexpr mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
    friend constexpr bool operator==(const mint& lhs, const mint& rhs) { return lhs.v_ == rhs.v_; }
    friend constexpr bool operator!=(const mint& lhs, const mint& rhs) { return lhs.v_ != rhs.v_; }
    friend std::istream& operator>>(std::istream& is, mint& x) {
        long long v;
        is >> v;
        x = mint(v);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const mint& x) { return os << x.val(); }

private:
    unsigned int v_;
};

template <int ID>
class dynamic_modint {
public:
    using mint = dynamic_modint;

    static int mod() { return mod_ref(); }
    static void set_mod(int m) {
        assert(m > 0);
        mod_ref() = m;
    }

    dynamic_modint() : v_(0) {}

    template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    dynamic_modint(T v) : v_(static_cast<unsigned int>(internal::safe_mod(static_cast<long long>(v), mod()))) {}

    static mint raw(int v) {
        mint x;
        x.v_ = static_cast<unsigned int>(v);
        return x;
    }

    int val() const { return static_cast<int>(v_); }

    mint operator+() const { return *this; }
    mint operator-() const { return v_ == 0 ? mint() : raw(mod() - static_cast<int>(v_)); }

    mint& operator+=(const mint& rhs) {
        v_ += rhs.v_;
        if (v_ >= static_cast<unsigned int>(mod())) v_ -= mod();
        return *this;
    }

    mint& operator-=(const mint& rhs) {
        if (v_ < rhs.v_) v_ += mod();
        v_ -= rhs.v_;
        return *this;
    }

    mint& operator*=(const mint& rhs) {
        v_ = static_cast<unsigned int>((static_cast<unsigned long long>(v_) * rhs.v_) % mod());
        return *this;
    }

    mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

    mint pow(long long n) const {
        assert(n >= 0);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }

    mint inv() const {
        auto [g, x] = internal::inv_gcd(v_, mod());
        assert(g == 1);
        return x;
    }

    friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs.v_ == rhs.v_; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs.v_ != rhs.v_; }
    friend std::istream& operator>>(std::istream& is, mint& x) {
        long long v;
        is >> v;
        x = mint(v);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const mint& x) { return os << x.val(); }

private:
    static int& mod_ref() {
        static int m = 998244353;
        return m;
    }

    unsigned int v_;
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<0>;

template <class Mint>
class mod_combination {
public:
    mod_combination() : fact_(1, Mint(1)), inv_fact_(1, Mint(1)), inv_(1, Mint(0)) {}
    explicit mod_combination(int n) : mod_combination() { reserve(n); }

    void reserve(int n) {
        if (n < static_cast<int>(fact_.size())) return;
        int old = static_cast<int>(fact_.size());
        fact_.resize(n + 1);
        inv_fact_.resize(n + 1);
        inv_.resize(n + 1);
        for (int i = old; i <= n; ++i) fact_[i] = fact_[i - 1] * i;
        inv_fact_[n] = fact_[n].inv();
        for (int i = n; i > old; --i) inv_fact_[i - 1] = inv_fact_[i] * i;
        for (int i = old; i <= n; ++i) inv_[i] = fact_[i - 1] * inv_fact_[i];
    }

    Mint fact(int n) {
        assert(n >= 0);
        reserve(n);
        return fact_[n];
    }

    Mint inv_fact(int n) {
        assert(n >= 0);
        reserve(n);
        return inv_fact_[n];
    }

    Mint inv(int n) {
        assert(n > 0);
        reserve(n);
        return inv_[n];
    }

    Mint C(long long n, long long k) {
        if (k < 0 || k > n) return 0;
        assert(n <= std::numeric_limits<int>::max());
        reserve(static_cast<int>(n));
        return fact_[n] * inv_fact_[k] * inv_fact_[n - k];
    }

    Mint P(long long n, long long k) {
        if (k < 0 || k > n) return 0;
        assert(n <= std::numeric_limits<int>::max());
        reserve(static_cast<int>(n));
        return fact_[n] * inv_fact_[n - k];
    }

    Mint H(long long n, long long k) {
        if (n == 0 && k == 0) return 1;
        if (n <= 0 || k < 0) return 0;
        return C(n + k - 1, k);
    }

private:
    std::vector<Mint> fact_;
    std::vector<Mint> inv_fact_;
    std::vector<Mint> inv_;
};

}  // namespace poe
