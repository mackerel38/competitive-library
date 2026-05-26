#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include <bits/stdc++.h>
using namespace std;

#include "structure/sparse_table.hpp"

int op(int a, int b) {
    return min(a, b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    poe::sparse_table<int, op> st(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.prod(l, r) << '\n';
    }
}
