#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "structure/segtree.hpp"

using mint = poe::modint998244353;

struct Affine {
    mint a, b;
};

Affine op(Affine l, Affine r) {
    return {l.a * r.a, l.b * r.a + r.b};
}

Affine e() {
    return {1, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<Affine> f(n);
    for (auto& x : f) cin >> x.a >> x.b;
    poe::segtree<Affine, op, e> seg(f);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            Affine x;
            cin >> p >> x.a >> x.b;
            seg.set(p, x);
        } else {
            int l, r;
            mint x;
            cin >> l >> r >> x;
            Affine f = seg.prod(l, r);
            cout << f.a * x + f.b << '\n';
        }
    }
}
