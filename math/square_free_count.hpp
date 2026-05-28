#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace poe {

namespace square_free_internal {

long long integer_sqrt(long long n) {
    long long x = static_cast<long long>(std::sqrt(static_cast<long double>(n)));
    while ((__int128)(x + 1) * (x + 1) <= n) ++x;
    while ((__int128)x * x > n) --x;
    return x;
}

std::vector<int> mobius_table(int n) {
    std::vector<int> min_factor(n + 1), primes, mu(n + 1);
    if (n >= 1) mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (min_factor[i] == 0) {
            min_factor[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (1LL * i * p > n || p > min_factor[i]) break;
            min_factor[i * p] = p;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

}  // namespace square_free_internal

long long count_square_free(long long n) {
    assert(n >= 0);
    if (n <= 33) {
        int r = static_cast<int>(square_free_internal::integer_sqrt(n));
        auto mu = square_free_internal::mobius_table(r);
        long long ans = 0;
        for (int i = 1; i <= r; ++i) ans += 1LL * mu[i] * (n / (1LL * i * i));
        return ans;
    }

    long long i_limit = std::max<long long>(1, std::pow(static_cast<long double>(n), 0.2L));
    int d_limit = static_cast<int>(square_free_internal::integer_sqrt(n / i_limit));
    auto mu = square_free_internal::mobius_table(d_limit);

    long long ans_small = 0;
    for (int i = 1; i <= d_limit; ++i) ans_small += 1LL * mu[i] * (n / (1LL * i * i));

    std::vector<long long> prefix(d_limit + 1);
    for (int i = 1; i <= d_limit; ++i) prefix[i] = prefix[i - 1] + mu[i];

    std::vector<long long> m_values;
    m_values.reserve(i_limit);
    long long sum_m = 0;
    for (long long i = i_limit - 1; i >= 1; --i) {
        long long x = square_free_internal::integer_sqrt(n / i);
        long long sqrt_x = square_free_internal::integer_sqrt(x);
        long long m_x = 1;
        for (long long j = 1; j <= x / (sqrt_x + 1); ++j) {
            m_x -= (x / j - x / (j + 1)) * prefix[j];
        }
        for (long long j = 2; j <= sqrt_x; ++j) {
            long long q = x / j;
            if (q <= d_limit) m_x -= prefix[q];
            else m_x -= m_values[i_limit - j * j * i - 1];
        }
        m_values.push_back(m_x);
        sum_m += m_x;
    }

    long long ans_large = sum_m - (i_limit - 1) * prefix.back();
    return ans_small + ans_large;
}

}  // namespace poe
