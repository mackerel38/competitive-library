#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class fenwick_tree_2d {
public:
    fenwick_tree_2d() = default;
    fenwick_tree_2d(int h, int w) : h_(h), w_(w), dense_(true), dense_data_(h, std::vector<T>(w)) {
        assert(h >= 0 && w >= 0);
    }
    explicit fenwick_tree_2d(const std::vector<std::pair<int, int>>& points) { build(points); }

    int height() const { return h_; }
    int width() const { return w_; }

    void build(std::vector<std::pair<int, int>> points) {
        dense_ = false;
        xs_.clear();
        for (auto [x, y] : points) xs_.push_back(x);
        std::sort(xs_.begin(), xs_.end());
        xs_.erase(std::unique(xs_.begin(), xs_.end()), xs_.end());
        h_ = static_cast<int>(xs_.size());
        w_ = 0;
        ys_.assign(h_ + 1, {});
        bit_.assign(h_ + 1, {});
        for (auto [x, y] : points) {
            int xi = xid(x);
            assert(xi < h_ && xs_[xi] == x);
            for (int i = xi + 1; i <= h_; i += i & -i) ys_[i].push_back(y);
        }
        for (int i = 1; i <= h_; ++i) {
            auto& ys = ys_[i];
            std::sort(ys.begin(), ys.end());
            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
            bit_[i].assign(ys.size(), T{});
        }
    }

    void add(int x, int y, T v) {
        if (dense_) {
            assert(0 <= x && x < h_);
            assert(0 <= y && y < w_);
            for (int i = x + 1; i <= h_; i += i & -i) {
                for (int j = y + 1; j <= w_; j += j & -j) dense_data_[i - 1][j - 1] += v;
            }
            return;
        }
        int xi = xid(x);
        assert(xi < h_ && xs_[xi] == x);
        for (int i = xi + 1; i <= h_; i += i & -i) {
            int yi = yid(i, y);
            assert(yi < static_cast<int>(ys_[i].size()) && ys_[i][yi] == y);
            for (int j = yi + 1; j <= static_cast<int>(bit_[i].size()); j += j & -j) bit_[i][j - 1] += v;
        }
    }

    T sum(int x, int y) const {
        if (dense_) {
            assert(0 <= x && x <= h_);
            assert(0 <= y && y <= w_);
            T res{};
            for (int i = x; i > 0; i -= i & -i) {
                for (int j = y; j > 0; j -= j & -j) res += dense_data_[i - 1][j - 1];
            }
            return res;
        }
        T res{};
        for (int i = xid(x); i > 0; i -= i & -i) {
            int yi = yid(i, y);
            for (int j = yi; j > 0; j -= j & -j) res += bit_[i][j - 1];
        }
        return res;
    }

    T sum(int xl, int xr, int yl, int yr) const {
        if (dense_) {
            assert(0 <= xl && xl <= xr && xr <= h_);
            assert(0 <= yl && yl <= yr && yr <= w_);
        } else {
            assert(xl <= xr);
            assert(yl <= yr);
        }
        return sum(xr, yr) - sum(xl, yr) - sum(xr, yl) + sum(xl, yl);
    }

    T range_sum(int xl, int xr, int yl, int yr) const { return sum(xl, xr, yl, yr); }
    T get(int x, int y) const { return sum(x, x + 1, y, y + 1); }

    void set(int x, int y, T v) {
        assert(0 <= x && x < h_);
        assert(0 <= y && y < w_);
        add(x, y, v - get(x, y));
    }

private:
    int xid(int x) const { return static_cast<int>(std::lower_bound(xs_.begin(), xs_.end(), x) - xs_.begin()); }
    int yid(int i, int y) const {
        return static_cast<int>(std::lower_bound(ys_[i].begin(), ys_[i].end(), y) - ys_[i].begin());
    }

    int h_ = 0;
    int w_ = 0;
    bool dense_ = true;
    std::vector<std::vector<T>> dense_data_;
    std::vector<int> xs_;
    std::vector<std::vector<int>> ys_;
    std::vector<std::vector<T>> bit_;
};

}  // namespace poe
