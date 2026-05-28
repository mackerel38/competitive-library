#pragma once

#include "structure/fenwick_tree_2d.hpp"

#include <cassert>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class rectangle_add_point_get {
public:
    rectangle_add_point_get() = default;

    explicit rectangle_add_point_get(const std::vector<std::pair<int, int>>& update_points) : bit_(update_points) {}

    struct rectangle {
        int l, d, r, u;
        T w;
    };

    static std::vector<std::pair<int, int>> collect_update_points(const std::vector<rectangle>& rectangles) {
        std::vector<std::pair<int, int>> points;
        points.reserve(rectangles.size() * 4);
        for (auto e : rectangles) {
            points.push_back({e.l, e.d});
            points.push_back({e.l, e.u});
            points.push_back({e.r, e.d});
            points.push_back({e.r, e.u});
        }
        return points;
    }

    void add_rectangle(int l, int d, int r, int u, T w) {
        assert(l <= r && d <= u);
        if (l == r || d == u || w == T{}) return;
        bit_.add(l, d, w);
        bit_.add(l, u, -w);
        bit_.add(r, d, -w);
        bit_.add(r, u, w);
    }

    void add_rectangle(const rectangle& e) { add_rectangle(e.l, e.d, e.r, e.u, e.w); }

    T get(int x, int y) const { return bit_.sum(x + 1, y + 1); }

private:
    fenwick_tree_2d<T> bit_;
};

}  // namespace poe
