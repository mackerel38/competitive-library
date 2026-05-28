#pragma once

#include "math/rational_approximation.hpp"

#include <string>
#include <vector>

namespace poe {

std::vector<std::pair<char, long long>> stern_brocot_path(long long p, long long q) {
    assert(p > 0 && q > 0);
    std::vector<std::pair<char, long long>> path;
    while (p != q) {
        if (p < q) {
            long long k = (q - 1) / p;
            path.push_back({'L', k});
            q -= k * p;
        } else {
            long long k = (p - 1) / q;
            path.push_back({'R', k});
            p -= k * q;
        }
    }
    return path;
}

rational stern_brocot_restore(const std::vector<std::pair<char, long long>>& path) {
    long long lnum = 0, lden = 1, rnum = 1, rden = 0;
    for (auto [dir, k] : path) {
        if (dir == 'L') {
            rnum += k * lnum;
            rden += k * lden;
        } else {
            lnum += k * rnum;
            lden += k * rden;
        }
    }
    return rational(lnum + rnum, lden + rden);
}

}  // namespace poe

