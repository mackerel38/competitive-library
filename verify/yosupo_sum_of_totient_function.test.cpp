#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"
#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "math/multiplicative_function.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    cout << poe::sum_totient<poe::modint998244353>(n) << '\n';
}
