#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class S, S (*op)(S, S), S (*e)()>
class segtree {
public:
    segtree() = default;
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : n_(static_cast<int>(v.size())) {
        size_ = 1;
        log_ = 0;
        while (size_ < n_) {
            size_ <<= 1;
            ++log_;
        }
        data_.assign(2 * size_, e());
        for (int i = 0; i < n_; ++i) data_[size_ + i] = v[i];
        for (int i = size_ - 1; i >= 1; --i) update(i);
    }

    int size() const { return n_; }

    void set(int p, S x) {
        assert(0 <= p && p < n_);
        p += size_;
        data_[p] = x;
        for (int i = 1; i <= log_; ++i) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < n_);
        return data_[p + size_];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n_);
        S sml = e(), smr = e();
        l += size_;
        r += size_;
        while (l < r) {
            if (l & 1) sml = op(sml, data_[l++]);
            if (r & 1) smr = op(data_[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return data_[1]; }

    template <bool (*f)(S)>
    int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= n_);
        assert(f(e()));
        if (l == n_) return n_;
        l += size_;
        S sm = e();
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!f(op(sm, data_[l]))) {
                while (l < size_) {
                    l <<= 1;
                    if (f(op(sm, data_[l]))) {
                        sm = op(sm, data_[l]);
                        ++l;
                    }
                }
                return l - size_;
            }
            sm = op(sm, data_[l]);
            ++l;
        } while ((l & -l) != l);
        return n_;
    }

    template <bool (*f)(S)>
    int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= n_);
        assert(f(e()));
        if (r == 0) return 0;
        r += size_;
        S sm = e();
        do {
            --r;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(op(data_[r], sm))) {
                while (r < size_) {
                    r = 2 * r + 1;
                    if (f(op(data_[r], sm))) {
                        sm = op(data_[r], sm);
                        --r;
                    }
                }
                return r + 1 - size_;
            }
            sm = op(data_[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    void update(int k) { data_[k] = op(data_[2 * k], data_[2 * k + 1]); }

    int n_ = 0;
    int size_ = 1;
    int log_ = 0;
    std::vector<S> data_ = {e(), e()};
};

}  // namespace poe
