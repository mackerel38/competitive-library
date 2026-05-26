#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
class lazy_segtree {
public:
    lazy_segtree() = default;
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : n_(static_cast<int>(v.size())) {
        size_ = 1;
        log_ = 0;
        while (size_ < n_) {
            size_ <<= 1;
            ++log_;
        }
        data_.assign(2 * size_, e());
        lazy_.assign(size_, id());
        for (int i = 0; i < n_; ++i) data_[size_ + i] = v[i];
        for (int i = size_ - 1; i >= 1; --i) update(i);
    }

    int size() const { return n_; }

    void set(int p, S x) {
        assert(0 <= p && p < n_);
        p += size_;
        for (int i = log_; i >= 1; --i) push(p >> i);
        data_[p] = x;
        for (int i = 1; i <= log_; ++i) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < n_);
        p += size_;
        for (int i = log_; i >= 1; --i) push(p >> i);
        return data_[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) return e();
        l += size_;
        r += size_;
        for (int i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, data_[l++]);
            if (r & 1) smr = op(data_[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return data_[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < n_);
        p += size_;
        for (int i = log_; i >= 1; --i) push(p >> i);
        data_[p] = mapping(f, data_[p]);
        for (int i = 1; i <= log_; ++i) update(p >> i);
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
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1;
            r >>= 1;
        }
        l = l2;
        r = r2;
        for (int i = 1; i <= log_; ++i) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)>
    int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }

    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= n_);
        assert(g(e()));
        if (l == n_) return n_;
        l += size_;
        for (int i = log_; i >= 1; --i) push(l >> i);
        S sm = e();
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!g(op(sm, data_[l]))) {
                while (l < size_) {
                    push(l);
                    l <<= 1;
                    if (g(op(sm, data_[l]))) {
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

    template <bool (*g)(S)>
    int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }

    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= n_);
        assert(g(e()));
        if (r == 0) return 0;
        r += size_;
        for (int i = log_; i >= 1; --i) push((r - 1) >> i);
        S sm = e();
        do {
            --r;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!g(op(data_[r], sm))) {
                while (r < size_) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(op(data_[r], sm))) {
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
    void all_apply(int k, F f) {
        data_[k] = mapping(f, data_[k]);
        if (k < size_) lazy_[k] = composition(f, lazy_[k]);
    }
    void push(int k) {
        all_apply(2 * k, lazy_[k]);
        all_apply(2 * k + 1, lazy_[k]);
        lazy_[k] = id();
    }

    int n_ = 0;
    int size_ = 1;
    int log_ = 0;
    std::vector<S> data_ = {e(), e()};
    std::vector<F> lazy_ = {id()};
};

}  // namespace poe
