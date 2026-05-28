#pragma once

#include "structure/fenwick_tree.hpp"

#include <algorithm>
#include <cassert>
#include <tuple>
#include <vector>

namespace poe {

template <class T>
class static_rectangle_add_rectangle_sum {
public:
    struct rectangle_add {
        long long l, d, r, u;
        T w;
    };
    struct rectangle_query {
        long long l, d, r, u;
    };

    static_rectangle_add_rectangle_sum() = default;
    static_rectangle_add_rectangle_sum(const std::vector<rectangle_add>& adds, const std::vector<rectangle_query>& queries) {
        solve(adds, queries);
    }

    const std::vector<T>& values() const { return answer_; }
    T get(int i) const {
        assert(0 <= i && i < static_cast<int>(answer_.size()));
        return answer_[i];
    }

private:
    struct event {
        long long x, y;
        T c;
    };
    struct prefix_query {
        long long x, y;
        int id;
        T sign;
    };
    struct sums {
        T c{}, cx{}, cy{}, cxy{};
        sums& operator+=(const sums& other) {
            c += other.c;
            cx += other.cx;
            cy += other.cy;
            cxy += other.cxy;
            return *this;
        }
        sums& operator-=(const sums& other) {
            c -= other.c;
            cx -= other.cx;
            cy -= other.cy;
            cxy -= other.cxy;
            return *this;
        }
        friend sums operator+(sums a, const sums& b) { return a += b; }
        friend sums operator-(sums a, const sums& b) { return a -= b; }
    };

    void solve(const std::vector<rectangle_add>& adds, const std::vector<rectangle_query>& queries) {
        std::vector<event> events;
        std::vector<long long> ys;
        events.reserve(adds.size() * 4);
        for (auto a : adds) {
            add_event(events, ys, a.l, a.d, a.w);
            add_event(events, ys, a.l, a.u, -a.w);
            add_event(events, ys, a.r, a.d, -a.w);
            add_event(events, ys, a.r, a.u, a.w);
        }
        std::vector<prefix_query> qs;
        qs.reserve(queries.size() * 4);
        for (int i = 0; i < static_cast<int>(queries.size()); ++i) {
            auto q = queries[i];
            qs.push_back({q.r, q.u, i, T(1)});
            qs.push_back({q.l, q.u, i, T(-1)});
            qs.push_back({q.r, q.d, i, T(-1)});
            qs.push_back({q.l, q.d, i, T(1)});
            ys.push_back(q.d);
            ys.push_back(q.u);
        }
        std::sort(ys.begin(), ys.end());
        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
        std::sort(events.begin(), events.end(), [](const event& a, const event& b) { return a.x < b.x; });
        std::sort(qs.begin(), qs.end(), [](const prefix_query& a, const prefix_query& b) { return a.x < b.x; });
        fenwick_tree<sums> fw(static_cast<int>(ys.size()) + 1);
        answer_.assign(queries.size(), T{});
        int ptr = 0;
        for (auto q : qs) {
            while (ptr < static_cast<int>(events.size()) && events[ptr].x < q.x) {
                int y = static_cast<int>(std::lower_bound(ys.begin(), ys.end(), events[ptr].y) - ys.begin());
                T xval = T(events[ptr].x);
                T yval = T(events[ptr].y);
                fw.add(y, {events[ptr].c, events[ptr].c * xval, events[ptr].c * yval, events[ptr].c * xval * yval});
                ++ptr;
            }
            int y = static_cast<int>(std::lower_bound(ys.begin(), ys.end(), q.y) - ys.begin());
            sums s = fw.sum(0, y);
            T xval = T(q.x);
            T yval = T(q.y);
            T pref = s.c * xval * yval - s.cx * yval - s.cy * xval + s.cxy;
            answer_[q.id] += q.sign * pref;
        }
    }

    void add_event(std::vector<event>& events, std::vector<long long>& ys, long long x, long long y, T c) {
        events.push_back({x, y, c});
        ys.push_back(y);
    }

    std::vector<T> answer_;
};

}  // namespace poe
