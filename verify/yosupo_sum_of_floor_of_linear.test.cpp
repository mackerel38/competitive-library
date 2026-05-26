#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
#include <bits/stdc++.h>
using namespace std;

#include "math/number_theory.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n, m, a, b;
        cin >> n >> m >> a >> b;
        cout << poe::floor_sum(n, m, a, b) << '\n';
    }
}
