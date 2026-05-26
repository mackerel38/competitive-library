#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"
#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "structure/dual_segtree.hpp"

using mint = poe::modint998244353;

struct F {
    mint a, b;
};

mint mapping(F f, mint x) {
    return f.a * x + f.b;
}

F composition(F f, F g) {
    return {g.a * f.a, g.b * f.a + f.b};
}

F id() {
    return {1, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<mint> a(n);
    for (auto& x : a) cin >> x;
    poe::dual_segtree<mint, F, mapping, composition, id> seg(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            F f;
            cin >> l >> r >> f.a >> f.b;
            seg.apply(l, r, f);
        } else {
            int p;
            cin >> p;
            cout << seg.get(p) << '\n';
        }
    }
}
