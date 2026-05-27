#pragma once

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class li_chao_tree {
public:
    struct line {
        T a, b;
        T get(T x) const { return a * x + b; }
    };

    li_chao_tree() = default;
    explicit li_chao_tree(std::vector<T> xs) : xs_(std::move(xs)) {
        std::sort(xs_.begin(), xs_.end());
        xs_.erase(std::unique(xs_.begin(), xs_.end()), xs_.end());
        n_ = static_cast<int>(xs_.size());
        seg_.assign(4 * std::max(1, n_), {T{}, inf()});
        used_.assign(4 * std::max(1, n_), false);
    }

    void add_line(T a, T b) { add_line({a, b}, 1, 0, n_); }

    void add_segment(T a, T b, T l, T r) {
        int li = static_cast<int>(std::lower_bound(xs_.begin(), xs_.end(), l) - xs_.begin());
        int ri = static_cast<int>(std::lower_bound(xs_.begin(), xs_.end(), r) - xs_.begin());
        add_segment({a, b}, li, ri, 1, 0, n_);
    }

    T get_min(T x) const {
        int p = static_cast<int>(std::lower_bound(xs_.begin(), xs_.end(), x) - xs_.begin());
        assert(p < n_ && xs_[p] == x);
        T res = inf();
        query(p, x, 1, 0, n_, res);
        return res;
    }

private:
    static constexpr T inf() { return std::numeric_limits<T>::max() / 4; }

    void add_line(line f, int k, int l, int r) {
        if (l >= r) return;
        if (!used_[k]) {
            seg_[k] = f;
            used_[k] = true;
            return;
        }
        int m = (l + r) >> 1;
        T xl = xs_[l], xm = xs_[m], xr = xs_[r - 1];
        line g = seg_[k];
        if (g.get(xm) > f.get(xm)) std::swap(seg_[k], f), g = seg_[k];
        if (r - l == 1) return;
        if (g.get(xl) > f.get(xl)) {
            add_line(f, k << 1, l, m);
        } else if (g.get(xr) > f.get(xr)) {
            add_line(f, k << 1 | 1, m, r);
        }
    }

    void add_segment(line f, int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            add_line(f, k, l, r);
            return;
        }
        int m = (l + r) >> 1;
        add_segment(f, a, b, k << 1, l, m);
        add_segment(f, a, b, k << 1 | 1, m, r);
    }

    void query(int p, T x, int k, int l, int r, T& res) const {
        if (used_[k]) res = std::min(res, seg_[k].get(x));
        if (r - l == 1) return;
        int m = (l + r) >> 1;
        if (p < m) query(p, x, k << 1, l, m, res);
        else query(p, x, k << 1 | 1, m, r, res);
    }

    int n_ = 0;
    std::vector<T> xs_;
    std::vector<line> seg_;
    std::vector<bool> used_;
};

}  // namespace poe
