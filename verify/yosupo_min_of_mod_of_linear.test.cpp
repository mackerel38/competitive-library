#define PROBLEM "https://judge.yosupo.jp/problem/min_of_mod_of_linear"
#include <bits/stdc++.h>
using namespace std;

#include "math/min_of_mod_of_linear.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n, m, a, b;
        cin >> n >> m >> a >> b;
        cout << poe::min_of_mod_of_linear(n, m, a, b) << '\n';
    }
}
