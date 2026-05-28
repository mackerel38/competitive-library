#pragma once

#include <cassert>
#include <cstdint>

namespace poe {

namespace integer_kth_root_internal {

bool leq_pow(unsigned long long x, int k, unsigned long long n) {
    __uint128_t v = 1;
    for (int i = 0; i < k; ++i) {
        v *= x;
        if (v > n) return false;
    }
    return true;
}

}  // namespace integer_kth_root_internal

unsigned long long integer_kth_root(unsigned long long n, int k) {
    assert(k >= 1);
    if (k == 1 || n <= 1) return n;
    unsigned long long ok = 0, ng = 1;
    while (integer_kth_root_internal::leq_pow(ng, k, n)) {
        if (ng > (1ULL << 63)) {
            ng = ~0ULL;
            break;
        }
        ng <<= 1;
    }
    while (ng - ok > 1) {
        unsigned long long mid = ok + (ng - ok) / 2;
        if (integer_kth_root_internal::leq_pow(mid, k, n)) ok = mid;
        else ng = mid;
    }
    return ok;
}

}  // namespace poe

