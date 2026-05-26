#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <bits/stdc++.h>
using namespace std;

#include "structure/dsu.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    poe::dsu uf(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) {
            uf.merge(u, v);
        } else {
            cout << uf.same(u, v) << '\n';
        }
    }
}
