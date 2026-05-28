#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_sort_range_composite"
#include "math/modint.hpp"
#include "structure/range_sort_range_composite.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    using mint = poe::modint998244353;
    int n, q;
    cin >> n >> q;
    vector<poe::range_sort_range_composite<mint>::item> a(n);
    for (auto& e : a) cin >> e.p >> e.a >> e.b;
    poe::range_sort_range_composite<mint> ds(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i, p;
            mint a, b;
            cin >> i >> p >> a >> b;
            ds.set(i, {p, a, b});
        } else if (t == 1) {
            int l, r;
            mint x;
            cin >> l >> r >> x;
            cout << ds.apply(l, r, x) << '\n';
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            ds.sort_ascending(l, r);
        } else {
            int l, r;
            cin >> l >> r;
            ds.sort_descending(l, r);
        }
    }
}
