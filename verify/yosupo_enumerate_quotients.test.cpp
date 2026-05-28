#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"
#include <bits/stdc++.h>
using namespace std;

#include "math/enumerate_quotients.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    auto qs = poe::quotient_values(n);
    reverse(qs.begin(), qs.end());
    cout << qs.size() << '\n';
    for (int i = 0; i < static_cast<int>(qs.size()); ++i) {
        if (i) cout << ' ';
        cout << qs[i];
    }
    cout << '\n';
}
