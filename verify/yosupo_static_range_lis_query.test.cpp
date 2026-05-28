#define PROBLEM "https://judge.yosupo.jp/problem/static_range_lis_query"
#include "structure/offline_static_range_lis_query.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> p(n);
    for (auto& x : p) cin >> x;
    poe::offline_static_range_lis_query ds(p);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        ds.add_query(l, r);
    }
    auto ans = ds.solve();
    for (int x : ans) cout << x << '\n';
}
