#define PROBLEM "https://judge.yosupo.jp/problem/rational_approximation"
#include <bits/stdc++.h>
using namespace std;

#include "math/rational_approximation.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n, x, y;
        cin >> n >> x >> y;
        auto [lo, hi] = poe::rational_approximation_bounded(n, x, y);
        cout << lo.num << ' ' << lo.den << ' ' << hi.num << ' ' << hi.den << '\n';
    }
}
