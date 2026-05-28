#pragma once

#include "structure/fenwick_tree.hpp"
#include "structure/mo.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace poe {

template <class T>
class offline_static_range_inversions_query {
public:
    offline_static_range_inversions_query() = default;
    explicit offline_static_range_inversions_query(const std::vector<T>& a) : n_(static_cast<int>(a.size())) {
        values_ = a;
        std::sort(values_.begin(), values_.end());
        values_.erase(std::unique(values_.begin(), values_.end()), values_.end());
        a_.resize(n_);
        for (int i = 0; i < n_; ++i) {
            a_[i] = static_cast<int>(std::lower_bound(values_.begin(), values_.end(), a[i]) - values_.begin());
        }
        mo_ = mo(n_);
    }

    int add_query(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        return mo_.add_query(l, r);
    }

    std::vector<long long> solve() const {
        fenwick_tree<int> fw(static_cast<int>(values_.size()));
        std::vector<long long> ans(mo_.size());
        long long inv = 0;
        auto add_left = [&](int i) {
            inv += fw.sum(0, a_[i]);
            fw.add(a_[i], 1);
        };
        auto add_right = [&](int i) {
            inv += fw.sum(a_[i] + 1, fw.size());
            fw.add(a_[i], 1);
        };
        auto erase_left = [&](int i) {
            fw.add(a_[i], -1);
            inv -= fw.sum(0, a_[i]);
        };
        auto erase_right = [&](int i) {
            fw.add(a_[i], -1);
            inv -= fw.sum(a_[i] + 1, fw.size());
        };
        mo_.run(add_left, add_right, erase_left, erase_right, [&](int id) { ans[id] = inv; });
        return ans;
    }

private:
    int n_ = 0;
    std::vector<T> values_;
    std::vector<int> a_;
    mo mo_{0};
};

}  // namespace poe
