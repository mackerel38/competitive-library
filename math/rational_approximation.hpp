#pragma once

#include <cassert>
#include <numeric>
#include <utility>

namespace poe {

struct rational {
    long long num;
    long long den;

    rational(long long n = 0, long long d = 1) : num(n), den(d) {
        if (den == 0) {
            assert(num > 0);
            num = 1;
            return;
        }
        if (den < 0) {
            num = -num;
            den = -den;
        }
        long long g = std::gcd(num >= 0 ? num : -num, den);
        num /= g;
        den /= g;
    }
};

bool operator==(const rational& lhs, const rational& rhs) {
    return (__int128)lhs.num * rhs.den == (__int128)rhs.num * lhs.den;
}

bool operator<=(const rational& lhs, const rational& rhs) {
    return (__int128)lhs.num * rhs.den <= (__int128)rhs.num * lhs.den;
}

rational stern_brocot_linear_combination(const rational& a, long long k, const rational& b) {
    return rational(a.num * k + b.num, a.den * k + b.den);
}

std::pair<rational, rational> rational_approximation(long long n, long long d, long long max_den) {
    assert(d > 0 && max_den >= 1);
    rational x(n, d);
    long long a = 0, b = 1, c = 1, e = 0;
    while (b + e <= max_den) {
        long long p = a + c, q = b + e;
        if ((__int128)p * x.den <= (__int128)x.num * q) {
            a = p;
            b = q;
        } else {
            c = p;
            e = q;
        }
    }
    return {rational(a, b), rational(c, e)};
}

std::pair<rational, rational> rational_approximation_bounded(long long n, long long x, long long y) {
    assert(n >= 1 && x >= 0 && y >= 1);
    rational target(x, y);
    rational lower(0, 1), upper(1, 0);
    auto in_bound = [&](const rational& f) { return f.num <= n && f.den <= n; };
    auto max_k = [&](const rational& a, const rational& b, auto pred) {
        long long ok = 0, ng = 1;
        while (true) {
            rational f = stern_brocot_linear_combination(a, ng, b);
            if (!in_bound(f) || !pred(f)) break;
            ng *= 2;
        }
        while (ng - ok > 1) {
            long long mid = (ok + ng) / 2;
            rational f = stern_brocot_linear_combination(a, mid, b);
            if (in_bound(f) && pred(f)) ok = mid;
            else ng = mid;
        }
        return ok;
    };
    while (true) {
        long long left_steps = max_k(upper, lower, [&](const rational& f) { return f <= target; });
        lower = stern_brocot_linear_combination(upper, left_steps, lower);
        if (lower == target) {
            upper = lower;
            break;
        }

        long long right_steps = max_k(lower, upper, [&](const rational& f) { return target <= f; });
        upper = stern_brocot_linear_combination(lower, right_steps, upper);
        if (upper == target) {
            lower = upper;
            break;
        }
        if (left_steps == 0 && right_steps == 0) break;
    }
    return {lower, upper};
}

rational best_rational_approximation(long long n, long long d, long long max_den) {
    assert(d > 0 && max_den >= 1);
    rational x(n, d), best(0, 1);
    __int128 best_num = -1, best_den = 1;
    for (long long q = 1; q <= max_den; ++q) {
        long long p = ((__int128)n * q + d / 2) / d;
        for (long long cand : {p - 1, p, p + 1}) {
            rational r(cand, q);
            __int128 diff_num = ((__int128)r.num * x.den - (__int128)x.num * r.den);
            if (diff_num < 0) diff_num = -diff_num;
            __int128 diff_den = (__int128)r.den * x.den;
            if (best_num < 0 || diff_num * best_den < best_num * diff_den) {
                best = r;
                best_num = diff_num;
                best_den = diff_den;
            }
        }
    }
    return best;
}

}  // namespace poe
