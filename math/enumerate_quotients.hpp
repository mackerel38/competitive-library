#pragma once

#include <cassert>
#include <vector>

namespace poe {

struct quotient_range {
    long long l;
    long long r;
    long long q;
};

std::vector<quotient_range> enumerate_quotients(long long n) {
    assert(n >= 0);
    std::vector<quotient_range> res;
    for (long long l = 1; l <= n;) {
        long long q = n / l;
        long long r = n / q + 1;
        res.push_back({l, r, q});
        l = r;
    }
    return res;
}

std::vector<long long> quotient_values(long long n) {
    std::vector<long long> res;
    for (auto [l, r, q] : enumerate_quotients(n)) {
        (void)l;
        (void)r;
        res.push_back(q);
    }
    return res;
}

}  // namespace poe

