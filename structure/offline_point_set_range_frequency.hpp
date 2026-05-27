#pragma once

#include "structure/fenwick_tree.hpp"

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class offline_point_set_range_frequency {
public:
    offline_point_set_range_frequency() = default;

    offline_point_set_range_frequency(const std::vector<T>& initial, const std::vector<std::pair<int, T>>& future_sets)
        : n_(static_cast<int>(initial.size())), current_(initial) {
        values_ = initial;
        for (auto [pos, value] : future_sets) {
            assert(0 <= pos && pos < n_);
            values_.push_back(value);
        }
        std::sort(values_.begin(), values_.end());
        values_.erase(std::unique(values_.begin(), values_.end()), values_.end());

        positions_.assign(values_.size(), {});
        for (int i = 0; i < n_; ++i) positions_[id(initial[i])].push_back(i);
        for (auto [pos, value] : future_sets) positions_[id(value)].push_back(pos);

        bit_.reserve(values_.size());
        for (auto& p : positions_) {
            std::sort(p.begin(), p.end());
            p.erase(std::unique(p.begin(), p.end()), p.end());
            bit_.emplace_back(static_cast<int>(p.size()));
        }
        for (int i = 0; i < n_; ++i) add(i, current_[i], 1);
    }

    int size() const { return n_; }
    T get(int p) const {
        assert(0 <= p && p < n_);
        return current_[p];
    }

    void set(int p, const T& value) {
        assert(0 <= p && p < n_);
        assert(contains_value(value));
        if (current_[p] == value) return;
        add(p, current_[p], -1);
        current_[p] = value;
        add(p, current_[p], 1);
    }

    int count(int l, int r, const T& value) const {
        assert(0 <= l && l <= r && r <= n_);
        int k = lower_id(value);
        if (k == static_cast<int>(values_.size()) || values_[k] != value) return 0;
        const auto& p = positions_[k];
        int li = static_cast<int>(std::lower_bound(p.begin(), p.end(), l) - p.begin());
        int ri = static_cast<int>(std::lower_bound(p.begin(), p.end(), r) - p.begin());
        return bit_[k].sum(li, ri);
    }

private:
    bool contains_value(const T& value) const {
        int k = lower_id(value);
        return k < static_cast<int>(values_.size()) && values_[k] == value;
    }

    int lower_id(const T& value) const {
        return static_cast<int>(std::lower_bound(values_.begin(), values_.end(), value) - values_.begin());
    }

    int id(const T& value) const {
        int k = lower_id(value);
        assert(k < static_cast<int>(values_.size()) && values_[k] == value);
        return k;
    }

    void add(int p, const T& value, int delta) {
        int k = id(value);
        const auto& pos = positions_[k];
        int j = static_cast<int>(std::lower_bound(pos.begin(), pos.end(), p) - pos.begin());
        assert(j < static_cast<int>(pos.size()) && pos[j] == p);
        bit_[k].add(j, delta);
    }

    int n_ = 0;
    std::vector<T> current_;
    std::vector<T> values_;
    std::vector<std::vector<int>> positions_;
    std::vector<fenwick_tree<int>> bit_;
};

}  // namespace poe
