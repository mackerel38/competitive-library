#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"
#include <bits/stdc++.h>
using namespace std;

#include "math/prime.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        long long p;
        cin >> p;
        cout << poe::primitive_root(p) << '\n';
    }
}
