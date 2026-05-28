#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <utility>
#include <vector>

namespace poe {

namespace prime_internal {

using u64 = std::uint64_t;
using u128 = __uint128_t;

u64 mod_mul(u64 a, u64 b, u64 mod) {
    return static_cast<u64>(static_cast<u128>(a) * b % mod);
}

u64 mod_pow(u64 a, u64 n, u64 mod) {
    u64 r = 1;
    while (n) {
        if (n & 1) r = mod_mul(r, a, mod);
        a = mod_mul(a, a, mod);
        n >>= 1;
    }
    return r;
}

bool miller_rabin(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = mod_pow(a % n, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (u64 r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2;
    static std::mt19937_64 rng(std::random_device{}());
    while (true) {
        u64 c = std::uniform_int_distribution<u64>(1, n - 1)(rng);
        u64 x = std::uniform_int_distribution<u64>(0, n - 1)(rng);
        u64 y = x;
        u64 d = 1;
        auto f = [&](u64 v) { return (mod_mul(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            u64 diff = x > y ? x - y : y - x;
            d = std::gcd(diff, n);
        }
        if (d != n) return d;
    }
}

void factor_rec(u64 n, std::vector<u64>& res) {
    if (n == 1) return;
    if (miller_rabin(n)) {
        res.push_back(n);
        return;
    }
    u64 d = pollard_rho(n);
    factor_rec(d, res);
    factor_rec(n / d, res);
}

}  // namespace prime_internal

bool is_prime(long long n) {
    return n >= 0 && prime_internal::miller_rabin(static_cast<prime_internal::u64>(n));
}

std::vector<int> sieve(int n) {
    if (n < 2) return {};
    std::vector<int> primes;
    primes.reserve(n >= 17 ? static_cast<std::size_t>(1.1 * n / std::log(n)) : 6);
    primes.push_back(2);
    int odd_count = (n + 1) / 2;
    std::vector<std::uint64_t> composite((odd_count + 63) >> 6, 0);
    auto get = [&](int i) -> bool { return (composite[i >> 6] >> (i & 63)) & 1ULL; };
    auto set = [&](int i) { composite[i >> 6] |= 1ULL << (i & 63); };
    set(0);
    for (long long p = 3; p * p <= n; p += 2) {
        int pi = static_cast<int>(p >> 1);
        if (get(pi)) continue;
        for (long long j = p * p; j <= n; j += p << 1) set(static_cast<int>(j >> 1));
    }
    for (int w = 0; w < static_cast<int>(composite.size()); ++w) {
        std::uint64_t bits = ~composite[w];
        if (w + 1 == static_cast<int>(composite.size()) && (odd_count & 63)) {
            bits &= (1ULL << (odd_count & 63)) - 1;
        }
        while (bits) {
            int b = __builtin_ctzll(bits);
            primes.push_back(2 * (w * 64 + b) + 1);
            bits &= bits - 1;
        }
    }
    return primes;
}

class linear_sieve {
public:
    linear_sieve() = default;
    explicit linear_sieve(int n) { build(n); }

    void build(int n) {
        assert(n >= 0);
        min_factor_.assign(n + 1, 0);
        primes_.clear();
        for (int i = 2; i <= n; ++i) {
            if (min_factor_[i] == 0) {
                min_factor_[i] = i;
                primes_.push_back(i);
            }
            for (int p : primes_) {
                if (p > min_factor_[i] || 1LL * i * p > n) break;
                min_factor_[i * p] = p;
            }
        }
    }

    const std::vector<int>& primes() const { return primes_; }
    int min_factor(int x) const {
        assert(0 <= x && x < static_cast<int>(min_factor_.size()));
        return min_factor_[x];
    }

    bool is_prime(int x) const {
        assert(0 <= x && x < static_cast<int>(min_factor_.size()));
        return x >= 2 && min_factor_[x] == x;
    }

    std::vector<std::pair<int, int>> factorize(int x) const {
        assert(1 <= x && x < static_cast<int>(min_factor_.size()));
        std::vector<std::pair<int, int>> res;
        while (x > 1) {
            int p = min_factor_[x], e = 0;
            while (x % p == 0) {
                x /= p;
                ++e;
            }
            res.push_back({p, e});
        }
        return res;
    }

private:
    std::vector<int> min_factor_;
    std::vector<int> primes_;
};

std::vector<std::pair<long long, int>> factorize(long long n) {
    assert(n >= 1);
    std::vector<prime_internal::u64> fs;
    prime_internal::factor_rec(static_cast<prime_internal::u64>(n), fs);
    std::sort(fs.begin(), fs.end());
    std::vector<std::pair<long long, int>> res;
    for (auto p : fs) {
        if (res.empty() || res.back().first != static_cast<long long>(p)) res.push_back({static_cast<long long>(p), 1});
        else ++res.back().second;
    }
    return res;
}

std::vector<long long> divisors(long long n) {
    assert(n >= 1);
    auto fs = factorize(n);
    std::vector<long long> res{1};
    for (auto [p, e] : fs) {
        int sz = static_cast<int>(res.size());
        long long mul = 1;
        for (int i = 1; i <= e; ++i) {
            mul *= p;
            for (int j = 0; j < sz; ++j) res.push_back(res[j] * mul);
        }
    }
    std::sort(res.begin(), res.end());
    return res;
}

long long euler_phi(long long n) {
    assert(n >= 1);
    long long res = n;
    for (auto [p, e] : factorize(n)) {
        (void)e;
        res = res / p * (p - 1);
    }
    return res;
}

long long primitive_root(long long mod) {
    assert(mod >= 2);
    if (mod == 2) return 1;
    long long phi = mod - 1;
    auto fs = factorize(phi);
    for (long long g = 2;; ++g) {
        bool ok = true;
        for (auto [p, e] : fs) {
            (void)e;
            if (prime_internal::mod_pow(g, phi / p, mod) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

}  // namespace poe
