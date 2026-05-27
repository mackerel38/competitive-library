#define PROBLEM "https://judge.yosupo.jp/problem/majority_voting"
#include "structure/offline_range_majority.hpp"

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
        int type, a, b;
    };
    vector<query> queries;
    vector<pair<int, int>> future_sets;
    for (int i = 0; i < q; ++i) {
        int t, x, y;
        cin >> t >> x >> y;
        queries.push_back({t, x, y});
        if (t == 0) future_sets.push_back({x, y});
    }
    poe::offline_range_majority<int> ds(a, future_sets);
    for (auto [type, x, y] : queries) {
        if (type == 0) {
            ds.set(x, y);
        } else {
            auto ans = ds.majority(x, y);
            cout << (ans ? *ans : -1) << '\n';
        }
    }
}
