#pragma once

#include "math/modint.hpp"

#include <cassert>
#include <unordered_map>
#include <vector>

namespace poe {

template <class T>
class totient_sum {
public:
    T sum(long long n) {
        if (n <= 0) return 0;
        if (n < static_cast<long long>(memo_small_.size()) && used_small_[n]) return memo_small_[n];
        if (auto it = memo_.find(n); it != memo_.end()) return it->second;
        T res = T(n) * T(n + 1) / T(2);
        for (long long l = 2; l <= n;) {
            long long q = n / l;
            long long r = n / q + 1;
            res -= T(r - l) * sum(q);
            l = r;
        }
        if (n < static_cast<long long>(memo_small_.size())) {
            used_small_[n] = true;
            return memo_small_[n] = res;
        }
        return memo_[n] = res;
    }

    explicit totient_sum(int small_limit = 1000000) : memo_small_(small_limit + 1), used_small_(small_limit + 1, false) {}

private:
    std::vector<T> memo_small_;
    std::vector<bool> used_small_;
    std::unordered_map<long long, T> memo_;
};

template <class T>
T sum_totient(long long n) {
    totient_sum<T> solver;
    return solver.sum(n);
}

}  // namespace poe

