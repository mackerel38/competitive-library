#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
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
        vector<long long> primes;
        for (auto [p, e] : poe::factorize(n)) {
            while (e--) primes.push_back(p);
        }
        cout << primes.size();
        for (long long p : primes) cout << ' ' << p;
        cout << '\n';
    }
}
