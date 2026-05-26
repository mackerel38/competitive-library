#pragma once

#include <cassert>
#include <utility>
#include <vector>

namespace poe {

class rollback_dsu {
public:
    rollback_dsu() = default;
    explicit rollback_dsu(int n) : parent_or_size_(n, -1), components_(n) {}

    int size() const { return static_cast<int>(parent_or_size_.size()); }
    int components() const { return components_; }
    int time() const { return static_cast<int>(history_.size()); }
    int snapshot() const { return time(); }

    int leader(int a) const {
        assert(0 <= a && a < size());
        while (parent_or_size_[a] >= 0) a = parent_or_size_[a];
        return a;
    }

    bool same(int a, int b) const {
        assert(0 <= a && a < size());
        assert(0 <= b && b < size());
        return leader(a) == leader(b);
    }

    int size(int a) const {
        assert(0 <= a && a < size());
        return -parent_or_size_[leader(a)];
    }

    bool merge(int a, int b) {
        assert(0 <= a && a < size());
        assert(0 <= b && b < size());
        a = leader(a);
        b = leader(b);
        history_.push_back({a, parent_or_size_[a]});
        history_.push_back({b, parent_or_size_[b]});
        if (a == b) return false;
        if (-parent_or_size_[a] < -parent_or_size_[b]) std::swap(a, b);
        parent_or_size_[a] += parent_or_size_[b];
        parent_or_size_[b] = a;
        --components_;
        return true;
    }

    void undo() {
        assert(static_cast<int>(history_.size()) >= 2);
        for (int i = 0; i < 2; ++i) {
            auto [v, value] = history_.back();
            history_.pop_back();
            if (parent_or_size_[v] != value && parent_or_size_[v] >= 0) ++components_;
            parent_or_size_[v] = value;
        }
    }

    void rollback(int t) {
        assert(0 <= t && t <= time());
        while (time() > t) undo();
    }

private:
    std::vector<int> parent_or_size_;
    std::vector<std::pair<int, int>> history_;
    int components_ = 0;
};

}  // namespace poe
