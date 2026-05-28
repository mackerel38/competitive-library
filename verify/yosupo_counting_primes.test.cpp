#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"
#include <bits/stdc++.h>
using namespace std;

#include "math/prime_count.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    cout << poe::prime_count(n) << '\n';
}
