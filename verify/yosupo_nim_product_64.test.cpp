#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"
#include <bits/stdc++.h>
using namespace std;

#include "math/nim_product.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        unsigned long long a, b;
        cin >> a >> b;
        cout << poe::nim_product(a, b) << '\n';
    }
}
