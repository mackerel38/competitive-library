#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include <bits/stdc++.h>
using namespace std;

#include "structure/wavelet_matrix.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    poe::wavelet_matrix<int> wm(a);
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << wm.kth_smallest(l, r, k) << '\n';
    }
}
