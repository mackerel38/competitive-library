#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class static_range_mode_query {
public:
    static_range_mode_query() = default;
    explicit static_range_mode_query(const std::vector<T>& a) : n_(static_cast<int>(a.size())), original_(a) {
        values_ = a;
        std::sort(values_.begin(), values_.end());
        values_.erase(std::unique(values_.begin(), values_.end()), values_.end());
        comp_.resize(n_);
        positions_.assign(values_.size(), {});
        for (int i = 0; i < n_; ++i) {
            comp_[i] = static_cast<int>(std::lower_bound(values_.begin(), values_.end(), a[i]) - values_.begin());
            positions_[comp_[i]].push_back(i);
        }
        block_size_ = std::max(1, static_cast<int>(std::sqrt(std::max(1, n_))) + 1);
        block_count_ = (n_ + block_size_ - 1) / block_size_;
        table_.assign(block_count_ + 1, std::vector<std::pair<int, int>>(block_count_ + 1, {-1, 0}));
        std::vector<int> freq(values_.size());
        for (int lb = 0; lb < block_count_; ++lb) {
            std::fill(freq.begin(), freq.end(), 0);
            std::pair<int, int> best{-1, 0};
            for (int i = lb * block_size_; i < n_; ++i) {
                int x = comp_[i];
                int f = ++freq[x];
                if (f > best.second) best = {x, f};
                if ((i + 1) % block_size_ == 0 || i + 1 == n_) {
                    int rb = (i + 1 + block_size_ - 1) / block_size_;
                    table_[lb][rb] = best;
                }
            }
        }
    }

    int size() const { return n_; }

    std::pair<T, int> query(int l, int r) const {
        assert(0 <= l && l < r && r <= n_);
        int lb = (l + block_size_ - 1) / block_size_;
        int rb = r / block_size_;
        std::pair<int, int> best{-1, 0};
        if (lb <= rb) best = table_[lb][rb];
        auto test = [&](int idx) {
            int x = comp_[idx];
            int f = count_code(l, r, x);
            if (f > best.second) best = {x, f};
        };
        int left_end = std::min(r, lb * block_size_);
        for (int i = l; i < left_end; ++i) test(i);
        int right_begin = std::max(l, rb * block_size_);
        for (int i = right_begin; i < r; ++i) test(i);
        return {values_[best.first], best.second};
    }

private:
    int count_code(int l, int r, int x) const {
        const auto& p = positions_[x];
        return static_cast<int>(std::lower_bound(p.begin(), p.end(), r) - std::lower_bound(p.begin(), p.end(), l));
    }

    int n_ = 0;
    int block_size_ = 1;
    int block_count_ = 0;
    std::vector<T> original_;
    std::vector<T> values_;
    std::vector<int> comp_;
    std::vector<std::vector<int>> positions_;
    std::vector<std::vector<std::pair<int, int>>> table_;
};

}  // namespace poe
