#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

namespace poe {

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
    class segtree {
    public:
        explicit segtree(const std::vector<T>& ys) : ys_(ys), cover_(ys.size() * 4), len_(ys.size() * 4) {}
        void add(T l, T r, int x) { add(1, 0, static_cast<int>(ys_.size()) - 1, l, r, x); }
        T covered() const { return len_[1]; }

    private:
        void add(int k, int nl, int nr, T ql, T qr, int x) {
            if (ys_[nr] <= ql || qr <= ys_[nl]) return;
            if (ql <= ys_[nl] && ys_[nr] <= qr) {
                cover_[k] += x;
                pull(k, nl, nr);
                return;
            }
            int mid = (nl + nr) >> 1;
            add(k << 1, nl, mid, ql, qr, x);
            add(k << 1 | 1, mid, nr, ql, qr, x);
            pull(k, nl, nr);
        }
        void pull(int k, int nl, int nr) {
            if (cover_[k] > 0) len_[k] = ys_[nr] - ys_[nl];
            else if (nr - nl == 1) len_[k] = T{};
            else len_[k] = len_[k << 1] + len_[k << 1 | 1];
        }
        const std::vector<T>& ys_;
        std::vector<int> cover_;
        std::vector<T> len_;
    };
    segtree seg(ys);
    T ans{};
    T prev_x = events[0].x;
    int i = 0;
    while (i < static_cast<int>(events.size())) {
        T x = events[i].x;
        ans += (x - prev_x) * seg.covered();
        while (i < static_cast<int>(events.size()) && events[i].x == x) {
            seg.add(events[i].d, events[i].u, events[i].delta);
            ++i;
        }
        prev_x = x;
    }
    return ans;
}

}  // namespace poe
