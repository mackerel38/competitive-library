#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class S, S (*op)(S, S)>
class sparse_table {
public:
    sparse_table() = default;
    explicit sparse_table(const std::vector<S>& v) : n_(static_cast<int>(v.size())) {
        log_.assign(n_ + 1, 0);
        for (int i = 2; i <= n_; ++i) log_[i] = log_[i >> 1] + 1;
        table_.assign(log_[n_] + 1, std::vector<S>(n_));
        if (n_ == 0) return;
        table_[0] = v;
        for (int k = 1; k < static_cast<int>(table_.size()); ++k) {
            int len = 1 << k;
            for (int i = 0; i + len <= n_; ++i) {
                table_[k][i] = op(table_[k - 1][i], table_[k - 1][i + (len >> 1)]);
            }
        }
    }

    int size() const { return n_; }

    S get(int p) const {
        assert(0 <= p && p < n_);
        return table_[0][p];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l < r && r <= n_);
        int k = log_[r - l];
        return op(table_[k][l], table_[k][r - (1 << k)]);
    }

private:
    int n_ = 0;
    std::vector<int> log_;
    std::vector<std::vector<S>> table_;
};

}  // namespace poe
