#pragma once

#include <cassert>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class weighted_dsu {
public:
    weighted_dsu() = default;
    explicit weighted_dsu(int n) : parent_or_size_(n, -1), diff_weight_(n, T{}) {}

    int size() const { return static_cast<int>(parent_or_size_.size()); }

    int leader(int x) {
        assert(0 <= x && x < size());
        if (parent_or_size_[x] < 0) return x;
        int p = parent_or_size_[x];
        int r = leader(p);
        diff_weight_[x] += diff_weight_[p];
        return parent_or_size_[x] = r;
    }

    T weight(int x) {
        leader(x);
        return diff_weight_[x];
    }

    bool same(int x, int y) {
        assert(0 <= x && x < size());
        assert(0 <= y && y < size());
        return leader(x) == leader(y);
    }

    T diff(int x, int y) {
        assert(same(x, y));
        return weight(y) - weight(x);
    }

    bool merge(int x, int y, T w) {
        assert(0 <= x && x < size());
        assert(0 <= y && y < size());
        w += weight(x);
        w -= weight(y);
        x = leader(x);
        y = leader(y);
        if (x == y) return w == T{};
        if (-parent_or_size_[x] < -parent_or_size_[y]) {
            std::swap(x, y);
            w = -w;
        }
        parent_or_size_[x] += parent_or_size_[y];
        parent_or_size_[y] = x;
        diff_weight_[y] = w;
        return true;
    }

    int size(int x) {
        assert(0 <= x && x < size());
        return -parent_or_size_[leader(x)];
    }

private:
    std::vector<int> parent_or_size_;
    std::vector<T> diff_weight_;
};

template <class G, G (*op)(G, G), G (*inv)(G), G (*e)()>
class weighted_dsu_group {
public:
    weighted_dsu_group() = default;
    explicit weighted_dsu_group(int n) : parent_or_size_(n, -1), diff_weight_(n, e()) {}

    int size() const { return static_cast<int>(parent_or_size_.size()); }

    int leader(int x) {
        assert(0 <= x && x < size());
        if (parent_or_size_[x] < 0) return x;
        int p = parent_or_size_[x];
        int r = leader(p);
        diff_weight_[x] = op(diff_weight_[p], diff_weight_[x]);
        return parent_or_size_[x] = r;
    }

    G weight(int x) {
        leader(x);
        return diff_weight_[x];
    }

    bool same(int x, int y) { return leader(x) == leader(y); }

    G diff(int x, int y) {
        assert(same(x, y));
        return op(inv(weight(x)), weight(y));
    }

    bool merge(int x, int y, G w) {
        w = op(op(weight(x), w), inv(weight(y)));
        x = leader(x);
        y = leader(y);
        if (x == y) return w == e();
        if (-parent_or_size_[x] < -parent_or_size_[y]) {
            std::swap(x, y);
            w = inv(w);
        }
        parent_or_size_[x] += parent_or_size_[y];
        parent_or_size_[y] = x;
        diff_weight_[y] = w;
        return true;
    }

    int size(int x) { return -parent_or_size_[leader(x)]; }

private:
    std::vector<int> parent_or_size_;
    std::vector<G> diff_weight_;
};

}  // namespace poe
