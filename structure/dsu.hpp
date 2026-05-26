#pragma once

#include <cassert>
#include <utility>
#include <vector>

namespace poe {

class dsu {
public:
    dsu() = default;
    explicit dsu(int n) : parent_or_size_(n, -1) {}

    int size() const { return static_cast<int>(parent_or_size_.size()); }

    int merge(int a, int b) {
        assert(0 <= a && a < size());
        assert(0 <= b && b < size());
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size_[x] < -parent_or_size_[y]) std::swap(x, y);
        parent_or_size_[x] += parent_or_size_[y];
        parent_or_size_[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < size());
        assert(0 <= b && b < size());
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < size());
        if (parent_or_size_[a] < 0) return a;
        return parent_or_size_[a] = leader(parent_or_size_[a]);
    }

    int size(int a) {
        assert(0 <= a && a < size());
        return -parent_or_size_[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        int n = size();
        std::vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; ++i) {
            leader_buf[i] = leader(i);
            ++group_size[leader_buf[i]];
        }
        std::vector<std::vector<int>> res(n);
        for (int i = 0; i < n; ++i) res[i].reserve(group_size[i]);
        for (int i = 0; i < n; ++i) res[leader_buf[i]].push_back(i);
        std::vector<std::vector<int>> compact;
        compact.reserve(n);
        for (auto& g : res) {
            if (!g.empty()) compact.push_back(std::move(g));
        }
        return compact;
    }

private:
    std::vector<int> parent_or_size_;
};

}  // namespace poe
