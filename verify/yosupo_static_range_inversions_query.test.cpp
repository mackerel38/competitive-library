#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#include "structure/offline_static_range_inversions_query.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    poe::offline_static_range_inversions_query<int> ds(a);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        ds.add_query(l, r);
    }
    auto ans = ds.solve();
    for (long long x : ans) cout << x << '\n';
}
