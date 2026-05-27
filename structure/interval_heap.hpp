#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

namespace poe {

template <class T, class Compare = std::less<T>, std::enable_if_t<std::is_invocable_r_v<bool, Compare, T, T>, int> = 0>
class interval_heap {
public:
    using value_type = T;

    interval_heap() = default;
    explicit interval_heap(const Compare& comp) : comp_(comp) {}

    template <class It>
    interval_heap(It first, It last) {
        for (; first != last; ++first) push(*first);
    }

    int size() const { return static_cast<int>(data_.size()); }
    bool empty() const { return data_.empty(); }
    void reserve(int n) { data_.reserve(n); }

    const T& min() const {
        assert(!empty());
        return data_[0];
    }

    const T& max() const {
        assert(!empty());
        return data_[max_top_index()];
    }

    void push(const T& x) {
        data_.push_back(x);
        fix_up(size() - 1);
    }

    T pop_min() {
        assert(!empty());
        int idx = min_top_index();
        std::swap(data_[idx], data_.back());
        T res = std::move(data_.back());
        data_.pop_back();
        if (!empty()) fix_min_down(idx);
        return res;
    }

    T pop_max() {
        assert(!empty());
        int idx = max_top_index();
        std::swap(data_[idx], data_.back());
        T res = std::move(data_.back());
        data_.pop_back();
        if (!empty()) fix_max_down(idx);
        return res;
    }

private:
    int min_top_index() const { return 0; }
    int max_top_index() const { return size() >= 2 ? 1 : 0; }

    void fix_up(int idx) {
        int l = idx & ~1;
        int r = l | 1;
        if (r < size()) {
            if (comp_(data_[r], data_[l])) {
                std::swap(data_[l], data_[r]);
                idx ^= 1;
            }
            fix_min_up(l);
            fix_max_up(r);
        } else {
            fix_min_up(l);
            fix_max_up(l);
        }
    }

    void fix_min_up(int idx) {
        while (idx >= 2) {
            int p = min_parent(idx);
            if (!comp_(data_[idx], data_[p])) return;
            std::swap(data_[idx], data_[p]);
            idx = p;
        }
    }

    void fix_max_up(int idx) {
        while (idx >= 2) {
            int p = max_parent(idx);
            if (!comp_(data_[p], data_[idx])) return;
            std::swap(data_[idx], data_[p]);
            idx = p;
        }
    }

    void fix_min_down(int idx) {
        while (true) {
            int l = min_child_l(idx);
            int r = min_child_r(idx);
            if (l >= size()) {
                fix_up(idx);
                return;
            }
            int ch = (r < size() && comp_(data_[r], data_[l])) ? r : l;
            if (!comp_(data_[ch], data_[idx])) return;
            std::swap(data_[idx], data_[ch]);
            idx = ch;
        }
    }

    void fix_max_down(int idx) {
        while (true) {
            int l = max_child_l(idx);
            int r = max_child_r(idx);
            if (l >= size()) --l;
            if (r >= size()) --r;
            if (l >= size()) {
                fix_up(idx);
                return;
            }
            int ch = (r < size() && comp_(data_[l], data_[r])) ? r : l;
            if (!comp_(data_[idx], data_[ch])) return;
            std::swap(data_[idx], data_[ch]);
            idx = ch;
        }
    }

    static constexpr int min_parent(int idx) { return ((idx - 2) >> 2) << 1; }
    static constexpr int max_parent(int idx) { return min_parent(idx) | 1; }
    static constexpr int min_child_l(int idx) { return (idx + 1) << 1; }
    static constexpr int min_child_r(int idx) { return (idx + 2) << 1; }
    static constexpr int max_child_l(int idx) { return min_child_l(idx - 1) | 1; }
    static constexpr int max_child_r(int idx) { return min_child_r(idx - 1) | 1; }

    std::vector<T> data_;
    Compare comp_{};
};

}  // namespace poe
