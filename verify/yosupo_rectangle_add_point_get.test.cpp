#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"
#include "structure/rectangle_add_point_get.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    struct query {
        int t, l, d, r, u, x, y;
        long long w;
    };
    vector<query> initial(n), queries(q);
    vector<poe::rectangle_add_point_get<long long>::rectangle> rectangles;
    rectangles.reserve(n + q);
    for (auto& e : initial) {
        cin >> e.l >> e.d >> e.r >> e.u >> e.w;
        rectangles.push_back({e.l, e.d, e.r, e.u, e.w});
    }
    for (auto& e : queries) {
        cin >> e.t;
        if (e.t == 0) {
            cin >> e.l >> e.d >> e.r >> e.u >> e.w;
            rectangles.push_back({e.l, e.d, e.r, e.u, e.w});
        } else {
            cin >> e.x >> e.y;
        }
    }
    poe::rectangle_add_point_get<long long> ds(poe::rectangle_add_point_get<long long>::collect_update_points(rectangles));
    for (auto e : initial) ds.add_rectangle(e.l, e.d, e.r, e.u, e.w);
    for (auto e : queries) {
        if (e.t == 0) ds.add_rectangle(e.l, e.d, e.r, e.u, e.w);
        else cout << ds.get(e.x, e.y) << '\n';
    }
}
