#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include "structure/fenwick_tree.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    poe::fenwick_tree<long long> fw(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << fw.sum(l, r) << '\n';
    }
}
