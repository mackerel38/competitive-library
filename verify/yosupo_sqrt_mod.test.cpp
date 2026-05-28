#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include <bits/stdc++.h>
using namespace std;

#include "math/mod_sqrt.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long y, p;
        cin >> y >> p;
        cout << poe::mod_sqrt(y, p) << '\n';
    }
}
