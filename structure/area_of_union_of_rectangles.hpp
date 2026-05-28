#pragma once

#include "structure/lazy_segtree.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <limits>
#include <vector>

namespace poe {

namespace internal {

template <class T>
struct rectangle_union_node {
    int min_cover = std::numeric_limits<int>::max() / 2;
    T min_len = T{};
    T total_len = T{};
};

template <class T>
rectangle_union_node<T> rectangle_union_op(rectangle_union_node<T> l, rectangle_union_node<T> r) {
    rectangle_union_node<T> res;
    res.min_cover = std::min(l.min_cover, r.min_cover);
    if (l.min_cover == res.min_cover) res.min_len += l.min_len;
    if (r.min_cover == res.min_cover) res.min_len += r.min_len;
    res.total_len = l.total_len + r.total_len;
    return res;
}

template <class T>
rectangle_union_node<T> rectangle_union_e() {
    return {};
}

template <class T>
rectangle_union_node<T> rectangle_union_mapping(int f, rectangle_union_node<T> x) {
    x.min_cover += f;
    return x;
}

inline int rectangle_union_composition(int f, int g) {
    return f + g;
}

inline int rectangle_union_id() {
    return 0;
}

}  // namespace internal

template <class T>
T area_of_union_of_rectangles(const std::vector<std::array<T, 4>>& rects) {
    struct event {
        T x, d, u;
        int delta;
    };
    std::vector<event> events;
    std::vector<T> ys;
    events.reserve(rects.size() * 2);
    ys.reserve(rects.size() * 2);
    for (auto rc : rects) {
        T l = rc[0], d = rc[1], r = rc[2], u = rc[3];
        if (l == r || d == u) continue;
        events.push_back({l, d, u, 1});
        events.push_back({r, d, u, -1});
        ys.push_back(d);
        ys.push_back(u);
    }
    if (events.empty()) return T{};
    std::sort(ys.begin(), ys.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
    std::sort(events.begin(), events.end(), [](const event& a, const event& b) { return a.x < b.x; });
    using node = internal::rectangle_union_node<T>;
    std::vector<node> init(ys.size() - 1);
    for (int i = 0; i + 1 < static_cast<int>(ys.size()); ++i) {
        T len = ys[i + 1] - ys[i];
        init[i] = {0, len, len};
    }
    lazy_segtree<node, internal::rectangle_union_op<T>, internal::rectangle_union_e<T>,
                 int, internal::rectangle_union_mapping<T>, internal::rectangle_union_composition,
                 internal::rectangle_union_id>
        seg(init);
    T ans{};
    T prev_x = events[0].x;
    int i = 0;
    while (i < static_cast<int>(events.size())) {
        T x = events[i].x;
        node all = seg.all_prod();
        T covered = all.total_len - (all.min_cover == 0 ? all.min_len : T{});
        ans += (x - prev_x) * covered;
        while (i < static_cast<int>(events.size()) && events[i].x == x) {
            int l = static_cast<int>(std::lower_bound(ys.begin(), ys.end(), events[i].d) - ys.begin());
            int r = static_cast<int>(std::lower_bound(ys.begin(), ys.end(), events[i].u) - ys.begin());
            seg.apply(l, r, events[i].delta);
            ++i;
        }
        prev_x = x;
    }
    return ans;
}

}  // namespace poe
