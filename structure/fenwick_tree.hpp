#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class T>
class fenwick_tree {
public:
    fenwick_tree() = default;
    explicit fenwick_tree(int n) : n_(n), data_(n) {
        assert(n >= 0);
    }
    explicit fenwick_tree(const std::vector<T>& v) : fenwick_tree(static_cast<int>(v.size())) {
        for (int i = 0; i < n_; ++i) add(i, v[i]);
    }

    int size() const { return n_; }

    void add(int p, T x) {
        assert(0 <= p && p < n_);
        for (++p; p <= n_; p += p & -p) data_[p - 1] += x;
    }

    T sum(int r) const {
        assert(0 <= r && r <= n_);
        T s{};
        for (; r > 0; r -= r & -r) s += data_[r - 1];
        return s;
    }

    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n_);
        return sum(r) - sum(l);
    }

    T range_sum(int l, int r) const { return sum(l, r); }
    T all_sum() const { return sum(n_); }
    T get(int p) const { return sum(p, p + 1); }

    void set(int p, T x) {
        assert(0 <= p && p < n_);
        add(p, x - get(p));
    }

    int lower_bound(T w) const {
        if (w <= T{}) return 0;
        int x = 0;
        int k = 1;
        while ((k << 1) <= n_) k <<= 1;
        for (; k > 0; k >>= 1) {
            if (x + k <= n_ && data_[x + k - 1] < w) {
                w -= data_[x + k - 1];
                x += k;
            }
        }
        return x;
    }

private:
    int n_ = 0;
    std::vector<T> data_;
};

}  // namespace poe
