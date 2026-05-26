#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include <bits/stdc++.h>
using namespace std;

#include "math/prime.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        long long n;
        cin >> n;
        cout << (poe::is_prime(n) ? "Yes" : "No") << '\n';
    }
}
