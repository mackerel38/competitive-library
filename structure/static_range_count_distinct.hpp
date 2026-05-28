#pragma once

#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

namespace poe {

template <class T>
class static_range_count_distinct {
public:
    static_range_count_distinct() = default;
    explicit static_range_count_distinct(const std::vector<T>& a) : n_(static_cast<int>(a.size())) {
        roots_.assign(n_ + 1, 0);
        nodes_.push_back({});
        std::map<T, int> last;
        for (int i = 0; i < n_; ++i) {
            int root = roots_[i];
            auto it = last.find(a[i]);
            if (it != last.end()) root = add(root, 0, n_, it->second, -1);
            root = add(root, 0, n_, i, 1);
            roots_[i + 1] = root;
            last[a[i]] = i;
        }
    }

    int size() const { return n_; }

    int count(int l, int r) const {
        assert(0 <= l && l <= r && r <= n_);
        return sum(roots_[r], 0, n_, l, r);
    }

private:
    struct node {
        int left = 0;
        int right = 0;
        int sum = 0;
    };

    int clone(int v) {
        nodes_.push_back(nodes_[v]);
        return static_cast<int>(nodes_.size()) - 1;
    }

    int add(int v, int nl, int nr, int p, int x) {
        int nv = clone(v);
        nodes_[nv].sum += x;
        if (nr - nl == 1) return nv;
        int mid = (nl + nr) >> 1;
        if (p < mid) {
            nodes_[nv].left = add(nodes_[nv].left, nl, mid, p, x);
        } else {
            nodes_[nv].right = add(nodes_[nv].right, mid, nr, p, x);
        }
        return nv;
    }

    int sum(int v, int nl, int nr, int ql, int qr) const {
        if (!v || nr <= ql || qr <= nl) return 0;
        if (ql <= nl && nr <= qr) return nodes_[v].sum;
        int mid = (nl + nr) >> 1;
        return sum(nodes_[v].left, nl, mid, ql, qr) + sum(nodes_[v].right, mid, nr, ql, qr);
    }

    int n_ = 0;
    std::vector<int> roots_;
    std::vector<node> nodes_;
};

}  // namespace poe
