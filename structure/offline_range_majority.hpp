#pragma once

#include "structure/offline_point_set_range_frequency.hpp"

#include <algorithm>
#include <cassert>
#include <optional>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class offline_range_majority {
public:
    offline_range_majority() = default;

    offline_range_majority(const std::vector<T>& initial, const std::vector<std::pair<int, T>>& future_sets)
        : n_(static_cast<int>(initial.size())), freq_(initial, future_sets) {
        size_ = 1;
        while (size_ < n_) size_ <<= 1;
        data_.assign(2 * size_, candidate{T{}, 0});
        for (int i = 0; i < n_; ++i) data_[size_ + i] = {initial[i], 1};
        for (int i = size_ - 1; i > 0; --i) data_[i] = op(data_[i << 1], data_[i << 1 | 1]);
    }

    int size() const { return n_; }

    void set(int p, const T& value) {
        assert(0 <= p && p < n_);
        freq_.set(p, value);
        p += size_;
        data_[p] = {value, 1};
        while (p >>= 1) data_[p] = op(data_[p << 1], data_[p << 1 | 1]);
    }

    std::optional<T> majority(int l, int r) const {
        assert(0 <= l && l <= r && r <= n_);
        candidate cand = fold(l, r);
        if (cand.count == 0) return std::nullopt;
        int c = freq_.count(l, r, cand.value);
        if (c * 2 > r - l) return cand.value;
        return std::nullopt;
    }

    int count(int l, int r, const T& value) const { return freq_.count(l, r, value); }

private:
    struct candidate {
        T value;
        int count;
    };

    static candidate op(candidate a, candidate b) {
        if (a.count == 0) return b;
        if (b.count == 0) return a;
        if (a.value == b.value) return {a.value, a.count + b.count};
        if (a.count > b.count) return {a.value, a.count - b.count};
        return {b.value, b.count - a.count};
    }

    candidate fold(int l, int r) const {
        candidate left{T{}, 0}, right{T{}, 0};
        l += size_;
        r += size_;
        while (l < r) {
            if (l & 1) left = op(left, data_[l++]);
            if (r & 1) right = op(data_[--r], right);
            l >>= 1;
            r >>= 1;
        }
        return op(left, right);
    }

    int n_ = 0;
    int size_ = 1;
    offline_point_set_range_frequency<T> freq_;
    std::vector<candidate> data_;
};

}  // namespace poe
