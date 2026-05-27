#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound"
#include "structure/wavelet_matrix.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    poe::wavelet_matrix<long long> wm(a);
    while (q--) {
        int l, r;
        long long x;
        cin >> l >> r >> x;
        cout << wm.range_freq(l, r, x + 1) << ' ' << wm.range_sum_less(l, r, x + 1) << '\n';
    }
}
