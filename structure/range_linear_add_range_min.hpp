#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class range_linear_add_range_min {
public:
    range_linear_add_range_min() = default;
    explicit range_linear_add_range_min(const std::vector<T>& a) : n_(static_cast<int>(a.size())), value_(a) {
        block_size_ = std::max(1, static_cast<int>(std::sqrt(std::max(1, n_))) + 1);
        block_count_ = (n_ + block_size_ - 1) / block_size_;
        lazy_b_.assign(block_count_, T{});
        lazy_c_.assign(block_count_, T{});
        hull_.resize(block_count_);
        for (int b = 0; b < block_count_; ++b) rebuild(b);
    }

    int size() const { return n_; }

    void add(int l, int r, T b, T c) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) return;
        int lb = l / block_size_;
        int rb = (r - 1) / block_size_;
        if (lb == rb) {
            materialize(lb);
            for (int i = l; i < r; ++i) value_[i] += b * static_cast<T>(i) + c;
            rebuild(lb);
            return;
        }
        materialize(lb);
        for (int i = l; i < std::min(n_, (lb + 1) * block_size_); ++i) value_[i] += b * static_cast<T>(i) + c;
        rebuild(lb);
        materialize(rb);
        for (int i = rb * block_size_; i < r; ++i) value_[i] += b * static_cast<T>(i) + c;
        rebuild(rb);
        for (int k = lb + 1; k < rb; ++k) {
            lazy_b_[k] += b;
            lazy_c_[k] += c;
        }
    }

    T min(int l, int r) const {
        assert(0 <= l && l < r && r <= n_);
        T res = std::numeric_limits<T>::max();
        int lb = l / block_size_;
        int rb = (r - 1) / block_size_;
        if (lb == rb) {
            for (int i = l; i < r; ++i) res = std::min(res, value_[i] + lazy_b_[lb] * static_cast<T>(i) + lazy_c_[lb]);
            return res;
        }
        for (int i = l; i < std::min(n_, (lb + 1) * block_size_); ++i) {
            res = std::min(res, value_[i] + lazy_b_[lb] * static_cast<T>(i) + lazy_c_[lb]);
        }
        for (int i = rb * block_size_; i < r; ++i) {
            res = std::min(res, value_[i] + lazy_b_[rb] * static_cast<T>(i) + lazy_c_[rb]);
        }
        for (int k = lb + 1; k < rb; ++k) res = std::min(res, block_min(k));
        return res;
    }

private:
    struct line {
        T m;
        T b;
        long double left;
    };

    static long double intersect_x(const line& a, const line& b) {
        return static_cast<long double>(a.b - b.b) / static_cast<long double>(b.m - a.m);
    }

    void materialize(int k) {
        if (lazy_b_[k] == T{} && lazy_c_[k] == T{}) return;
        int l = k * block_size_;
        int r = std::min(n_, l + block_size_);
        for (int i = l; i < r; ++i) value_[i] += lazy_b_[k] * static_cast<T>(i) + lazy_c_[k];
        lazy_b_[k] = lazy_c_[k] = T{};
    }

    void rebuild(int k) {
        std::vector<line> lines;
        int l = k * block_size_;
        int r = std::min(n_, l + block_size_);
        lines.reserve(r - l);
        for (int i = l; i < r; ++i) lines.push_back({static_cast<T>(i), value_[i], -std::numeric_limits<long double>::infinity()});
        std::sort(lines.begin(), lines.end(), [](const line& a, const line& b) {
            if (a.m != b.m) return a.m > b.m;
            return a.b < b.b;
        });
        auto& h = hull_[k];
        h.clear();
        for (auto ln : lines) {
            if (!h.empty() && h.back().m == ln.m) continue;
            while (!h.empty()) {
                long double x = intersect_x(h.back(), ln);
                if (x > h.back().left) {
                    ln.left = x;
                    break;
                }
                h.pop_back();
            }
            if (h.empty()) ln.left = -std::numeric_limits<long double>::infinity();
            h.push_back(ln);
        }
    }

    T eval(const line& ln, T x) const { return ln.m * x + ln.b; }

    T block_min(int k) const {
        const auto& h = hull_[k];
        T x = lazy_b_[k];
        int id = static_cast<int>(std::upper_bound(h.begin(), h.end(), static_cast<long double>(x),
                                                   [](long double v, const line& ln) { return v < ln.left; }) -
                                  h.begin()) -
                 1;
        return eval(h[id], x) + lazy_c_[k];
    }

    int n_ = 0;
    int block_size_ = 1;
    int block_count_ = 0;
    std::vector<T> value_;
    std::vector<T> lazy_b_, lazy_c_;
    std::vector<std::vector<line>> hull_;
};

}  // namespace poe
