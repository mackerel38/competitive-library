#define PROBLEM "https://judge.yosupo.jp/problem/static_range_count_distinct"
#include "structure/static_range_count_distinct.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    poe::static_range_count_distinct<int> ds(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << ds.count(l, r) << '\n';
    }
}
