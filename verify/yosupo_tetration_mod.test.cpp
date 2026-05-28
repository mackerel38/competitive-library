#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"
#include <bits/stdc++.h>
using namespace std;

#include "math/tetration_mod.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long a, b, m;
        cin >> a >> b >> m;
        cout << poe::tetration_mod(a, b, m) << '\n';
    }
}
