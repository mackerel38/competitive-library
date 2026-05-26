#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include <bits/stdc++.h>
using namespace std;

#include "structure/fenwick_tree_2d.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    struct Point {
        int x, y;
        long long w;
    };
    struct Query {
        int t, a, b, c, d;
    };
    vector<Point> points(n);
    vector<pair<int, int>> add_points;
    for (auto& p : points) {
        cin >> p.x >> p.y >> p.w;
        add_points.push_back({p.x, p.y});
    }
    vector<Query> queries(q);
    for (auto& query : queries) {
        cin >> query.t;
        if (query.t == 0) {
            cin >> query.a >> query.b >> query.c;
            query.d = 0;
            add_points.push_back({query.a, query.b});
        } else {
            cin >> query.a >> query.b >> query.c >> query.d;
        }
    }
    poe::fenwick_tree_2d<long long> fw(add_points);
    for (auto p : points) fw.add(p.x, p.y, p.w);
    for (auto query : queries) {
        if (query.t == 0) {
            fw.add(query.a, query.b, query.c);
        } else {
            cout << fw.sum(query.a, query.c, query.b, query.d) << '\n';
        }
    }
}
