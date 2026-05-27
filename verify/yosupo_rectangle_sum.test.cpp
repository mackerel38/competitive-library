#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "structure/fenwick_tree_2d.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    struct point {
        int x, y;
        long long w;
    };
    vector<point> points(n);
    vector<pair<int, int>> coords;
    for (auto& p : points) {
        cin >> p.x >> p.y >> p.w;
        coords.push_back({p.x, p.y});
    }
    poe::fenwick_tree_2d<long long> fw(coords);
    for (auto p : points) fw.add(p.x, p.y, p.w);
    while (q--) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;
        cout << fw.sum(l, r, d, u) << '\n';
    }
}
