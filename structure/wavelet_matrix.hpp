#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace poe {

template <class T>
class wavelet_matrix {
public:
    wavelet_matrix() = default;
    explicit wavelet_matrix(const std::vector<T>& v) : n_(static_cast<int>(v.size())), original_(v) {
        values_ = v;
        std::sort(values_.begin(), values_.end());
        values_.erase(std::unique(values_.begin(), values_.end()), values_.end());
        int sigma = static_cast<int>(values_.size());
        while ((1 << log_) < sigma) ++log_;
        std::vector<int> cur(n_);
        for (int i = 0; i < n_; ++i) cur[i] = id(v[i]);
        matrix_.resize(log_);
        mid_.resize(log_);
        for (int level = log_ - 1; level >= 0; --level) {
            bit_vector bv(n_);
            std::vector<int> zero, one;
            zero.reserve(n_);
            one.reserve(n_);
            for (int i = 0; i < n_; ++i) {
                if ((cur[i] >> level) & 1) {
                    bv.set(i);
                    one.push_back(cur[i]);
                } else {
                    zero.push_back(cur[i]);
                }
            }
            bv.build();
            matrix_[level] = std::move(bv);
            mid_[level] = static_cast<int>(zero.size());
            zero.insert(zero.end(), one.begin(), one.end());
            cur.swap(zero);
        }
    }

    int size() const { return n_; }
    T access(int k) const {
        assert(0 <= k && k < n_);
        return original_[k];
    }
    T get(int k) const { return access(k); }

    int rank(int r, const T& x) const {
        assert(0 <= r && r <= n_);
        int k = lower_id(x);
        if (k == static_cast<int>(values_.size()) || values_[k] != x) return 0;
        return rank_code(r, k);
    }

    int rank(int l, int r, const T& x) const {
        assert(0 <= l && l <= r && r <= n_);
        return rank(r, x) - rank(l, x);
    }

    T kth_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= n_);
        assert(0 <= k && k < r - l);
        int code = 0;
        for (int level = log_ - 1; level >= 0; --level) {
            int l0 = matrix_[level].rank0(l);
            int r0 = matrix_[level].rank0(r);
            int zeros = r0 - l0;
            if (k < zeros) {
                l = l0;
                r = r0;
            } else {
                k -= zeros;
                code |= 1 << level;
                l = mid_[level] + matrix_[level].rank1(l);
                r = mid_[level] + matrix_[level].rank1(r);
            }
        }
        return values_[code];
    }

    T kth_largest(int l, int r, int k) const {
        assert(0 <= k && k < r - l);
        return kth_smallest(l, r, r - l - 1 - k);
    }

    int range_freq(int l, int r, const T& upper) const {
        assert(0 <= l && l <= r && r <= n_);
        return rank_less(l, r, lower_id(upper));
    }

    int range_freq(int l, int r, const T& lower, const T& upper) const {
        assert(lower <= upper);
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    T prev_value(int l, int r, const T& upper) const {
        int cnt = range_freq(l, r, upper);
        assert(cnt > 0);
        return kth_smallest(l, r, cnt - 1);
    }

    T next_value(int l, int r, const T& lower) const {
        int cnt = range_freq(l, r, lower);
        assert(cnt < r - l);
        return kth_smallest(l, r, cnt);
    }

private:
    class bit_vector {
    public:
        bit_vector() = default;
        explicit bit_vector(int n) : bits_(n), sum_(n + 1) {}
        void set(int k) { bits_[k] = 1; }
        void build() {
            for (int i = 0; i < static_cast<int>(bits_.size()); ++i) sum_[i + 1] = sum_[i] + bits_[i];
        }
        int rank1(int r) const { return sum_[r]; }
        int rank0(int r) const { return r - rank1(r); }

    private:
        std::vector<unsigned char> bits_;
        std::vector<int> sum_;
    };

    int lower_id(const T& x) const {
        return static_cast<int>(std::lower_bound(values_.begin(), values_.end(), x) - values_.begin());
    }

    int id(const T& x) const {
        auto it = std::lower_bound(values_.begin(), values_.end(), x);
        assert(it != values_.end() && *it == x);
        return static_cast<int>(it - values_.begin());
    }

    int rank_code(int r, int code) const {
        int l = 0;
        for (int level = log_ - 1; level >= 0; --level) {
            if ((code >> level) & 1) {
                l = mid_[level] + matrix_[level].rank1(l);
                r = mid_[level] + matrix_[level].rank1(r);
            } else {
                l = matrix_[level].rank0(l);
                r = matrix_[level].rank0(r);
            }
        }
        return r - l;
    }

    int rank_less(int l, int r, int upper_code) const {
        if (upper_code <= 0) return 0;
        if (upper_code >= static_cast<int>(values_.size())) return r - l;
        int res = 0;
        for (int level = log_ - 1; level >= 0; --level) {
            int l0 = matrix_[level].rank0(l);
            int r0 = matrix_[level].rank0(r);
            if ((upper_code >> level) & 1) {
                res += r0 - l0;
                l = mid_[level] + matrix_[level].rank1(l);
                r = mid_[level] + matrix_[level].rank1(r);
            } else {
                l = l0;
                r = r0;
            }
        }
        return res;
    }

    int n_ = 0;
    int log_ = 0;
    std::vector<T> original_;
    std::vector<T> values_;
    std::vector<bit_vector> matrix_;
    std::vector<int> mid_;
};

}  // namespace poe
