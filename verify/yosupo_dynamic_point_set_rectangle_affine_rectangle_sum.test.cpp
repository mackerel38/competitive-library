#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_point_set_rectangle_affine_rectangle_sum"
#include "math/modint.hpp"
#include "structure/kd_tree_rectangle_affine_sum.hpp"

#include <bits/stdc++.h>
using namespace std;

struct query {
    int type;
    long long x, y, l, d, r, u;
    poe::modint998244353 w, a, b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    using mint = poe::modint998244353;
    int n, q;
    cin >> n >> q;
    vector<poe::kd_tree_rectangle_affine_sum<mint>::point> points;
    points.reserve(n + q);
    for (int i = 0; i < n; ++i) {
        long long x, y;
        mint w;
        cin >> x >> y >> w;
        points.push_back({x, y, w, true});
    }
    vector<query> queries(q);
    for (auto& e : queries) {
        cin >> e.type;
        if (e.type == 0) {
            cin >> e.x >> e.y >> e.w;
            points.push_back({e.x, e.y, mint(0), false});
        } else if (e.type == 1) {
            cin >> e.x >> e.w;
        } else if (e.type == 2) {
            cin >> e.l >> e.d >> e.r >> e.u;
        } else {
            cin >> e.l >> e.d >> e.r >> e.u >> e.a >> e.b;
        }
    }
    poe::kd_tree_rectangle_affine_sum<mint> ds(points);
    int next_id = n;
    for (auto e : queries) {
        if (e.type == 0) {
            ds.activate(next_id++, e.w);
        } else if (e.type == 1) {
            ds.set(static_cast<int>(e.x), e.w);
        } else if (e.type == 2) {
            cout << ds.sum(e.l, e.d, e.r, e.u) << '\n';
        } else {
            ds.apply(e.l, e.d, e.r, e.u, {e.a, e.b});
        }
    }
}
