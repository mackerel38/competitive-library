#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class S, class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
class dual_segtree {
public:
    dual_segtree() = default;
    explicit dual_segtree(int n) : dual_segtree(std::vector<S>(n)) {}
    explicit dual_segtree(const std::vector<S>& v) : n_(static_cast<int>(v.size())), data_(v) {
        size_ = 1;
        log_ = 0;
        while (size_ < n_) {
            size_ <<= 1;
            ++log_;
        }
        lazy_.assign(2 * size_, id());
    }

    int size() const { return n_; }

    void set(int p, S x) {
        assert(0 <= p && p < n_);
        int k = p + size_;
        for (int i = log_; i >= 1; --i) push(k >> i);
        data_[p] = x;
        lazy_[k] = id();
    }

    S get(int p) {
        assert(0 <= p && p < n_);
        int k = p + size_;
        for (int i = log_; i >= 1; --i) push(k >> i);
        return mapping(lazy_[k], data_[p]);
    }

    void apply(int p, F f) {
        assert(0 <= p && p < n_);
        apply(p, p + 1, f);
    }

    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) return;
        l += size_;
        r += size_;
        for (int i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1;
            r >>= 1;
        }
    }

    std::vector<S> all_get() {
        std::vector<S> res(n_);
        for (int i = 0; i < n_; ++i) res[i] = get(i);
        return res;
    }

private:
    void all_apply(int k, F f) { lazy_[k] = composition(f, lazy_[k]); }
    void push(int k) {
        all_apply(2 * k, lazy_[k]);
        all_apply(2 * k + 1, lazy_[k]);
        lazy_[k] = id();
    }

    int n_ = 0;
    int size_ = 1;
    int log_ = 0;
    std::vector<S> data_;
    std::vector<F> lazy_ = {id(), id()};
};

}  // namespace poe
