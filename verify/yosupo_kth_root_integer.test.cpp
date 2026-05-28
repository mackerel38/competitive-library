#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"
#include <bits/stdc++.h>
using namespace std;

#include "math/integer_kth_root.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        unsigned long long a;
        int k;
        cin >> a >> k;
        cout << poe::integer_kth_root(a, k) << '\n';
    }
}
