#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"
#include "math/modint.hpp"
#include "structure/weighted_dsu.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    poe::weighted_dsu<poe::modint998244353> dsu(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) {
            int x;
            cin >> x;
            cout << dsu.merge(v, u, poe::modint998244353(x)) << '\n';
        } else {
            if (!dsu.same(u, v)) {
                cout << -1 << '\n';
            } else {
                cout << dsu.diff(v, u).val() << '\n';
            }
        }
    }
}
