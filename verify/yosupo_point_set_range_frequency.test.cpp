#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"
#include "structure/offline_point_set_range_frequency.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    struct query {
        int type, l, r, x;
    };
    vector<query> queries;
    vector<pair<int, int>> future_sets;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, x;
            cin >> p >> x;
            queries.push_back({t, p, 0, x});
            future_sets.push_back({p, x});
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            queries.push_back({t, l, r, x});
        }
    }
    poe::offline_point_set_range_frequency<int> ds(a, future_sets);
    for (auto [type, l, r, x] : queries) {
        if (type == 0) ds.set(l, x);
        else cout << ds.count(l, r, x) << '\n';
    }
}
