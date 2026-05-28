#pragma once

#include <algorithm>
#include <cassert>
#include <limits>

namespace poe {

namespace min_of_mod_internal {

using i128 = __int128_t;

long long floor_div(long long y, long long x) {
    assert(x != 0);
    if (x < 0) {
        x = -x;
        y = -y;
    }
    if (y >= 0) return y / x;
    return -static_cast<long long>((static_cast<i128>(-y) + x - 1) / x);
}

long long internal_floor_max(long long A, long long B, long long C, long long D, long long E, long long F) {
    constexpr long long neg_inf = std::numeric_limits<long long>::lowest() / 4;
    if (D < 0) return neg_inf;
    if (C <= 0) return neg_inf;
    if (E > 0) {
        if (B > C) {
            std::swap(A, E);
            std::swap(B, C);
        }
        long long cd = floor_div(D, C);
        long long bd = floor_div(D, B);
        long long m = floor_div(D - C * cd, B);
        long long bc = floor_div(C, B);
        long long shift = bc * cd + m + 1;
        long long edge = std::max(A * m + E * cd, A * bd) + F;
        long long next = internal_floor_max(A, B, C % B, D - B * shift, E - A * bc, F + A * shift);
        return std::max(edge, next);
    }
    return A * floor_div(D, B) + F;
}

long long floor_max(long long N, long long A, long long B, long long C, long long D, long long E, long long F) {
    constexpr long long neg_inf = std::numeric_limits<long long>::lowest() / 4;
    if (N < 0) return neg_inf;
    assert(B != 0);
    if (B < 0) {
        B = -B;
        C = -C;
        D = -D;
    }
    if (A < 0) {
        A = -A;
        C = -C;
        D = -D + B - 1;
    }
    if (C == 0 || A == 0) return A * floor_div(D, B) + F + std::max(0LL, E * N);
    if (E == 0) return A * floor_div(std::max(0LL, C * N) + D, B) + F;
    if (C > 0) {
        F += E * N;
        E = -E;
        D += C * N;
    } else {
        C = -C;
    }
    if (E < 0) return A * floor_div(D, B) + F;
    long long x_offset = floor_div(D - C * N, B) + 1;
    D -= B * x_offset;
    return A * x_offset + std::max(internal_floor_max(A, B, C, D, E, F), -A + E * N + F);
}

}  // namespace min_of_mod_internal

long long min_of_mod_of_linear(long long n, long long m, long long a, long long b) {
    assert(n >= 0 && m >= 1);
    if (n == 0) return 0;
    a %= m;
    if (a < 0) a += m;
    b %= m;
    if (b < 0) b += m;
    long long mx = min_of_mod_internal::floor_max(n - 1, m, m, a, b, -a, -b);
    return -mx;
}

}  // namespace poe

