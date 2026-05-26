#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include <bits/stdc++.h>
using namespace std;

#include "math/convolution.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<poe::modint998244353> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    auto c = poe::convolution(a, b);
    for (int i = 0; i < static_cast<int>(c.size()); ++i) {
        if (i) cout << ' ';
        cout << c[i];
    }
    cout << '\n';
}
