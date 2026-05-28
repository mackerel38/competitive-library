#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"
#include <bits/stdc++.h>
using namespace std;

#include "math/discrete_log.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long x, y, m;
        cin >> x >> y >> m;
        cout << poe::discrete_log(x, y, m) << '\n';
    }
}
