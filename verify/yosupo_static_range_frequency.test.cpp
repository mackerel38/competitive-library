#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include "structure/wavelet_matrix.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    poe::wavelet_matrix<int> wm(a);
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << wm.rank(l, r, x) << '\n';
    }
}
