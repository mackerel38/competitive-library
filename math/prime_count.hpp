#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace poe {

long long prime_count(long long n) {
    assert(n >= 0);
    if (n < 2) return 0;
    long long v = static_cast<long long>(std::sqrt(n));
    std::vector<long long> small(v + 1), large(v + 1);
    for (long long i = 1; i <= v; ++i) {
        small[i] = i - 1;
        large[i] = n / i - 1;
    }
    for (long long p = 2; p <= v; ++p) {
        if (small[p] == small[p - 1]) continue;
        long long pc = small[p - 1];
        long long q = p * p;
        for (long long i = 1; i <= v && i * q <= n; ++i) {
            long long d = i * p;
            if (d <= v) large[i] -= large[d] - pc;
            else large[i] -= small[n / d] - pc;
        }
        for (long long i = v; i >= q; --i) small[i] -= small[i / p] - pc;
    }
    return large[1];
}

}  // namespace poe

