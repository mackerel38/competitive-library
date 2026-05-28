#define PROBLEM "https://judge.yosupo.jp/problem/range_linear_add_range_min"
#include "structure/range_linear_add_range_min.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    poe::range_linear_add_range_min<long long> ds(a);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long b, c;
            cin >> b >> c;
            ds.add(l, r, b, c);
        } else {
            cout << ds.min(l, r) << '\n';
        }
    }
}
