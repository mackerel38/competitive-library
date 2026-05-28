#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"
#include <bits/stdc++.h>
using namespace std;

#include "math/prime.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    auto ps = poe::sieve(n);
    vector<int> ans;
    for (int i = b; i < static_cast<int>(ps.size()); i += a) ans.push_back(ps[i]);
    cout << ps.size() << ' ' << ans.size() << '\n';
    for (int i = 0; i < static_cast<int>(ans.size()); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
