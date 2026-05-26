#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "structure/lazy_segtree.hpp"

using mint = poe::modint998244353;

struct S {
    mint sum;
    int len;
};

struct F {
    mint a, b;
};

S op(S l, S r) {
    return {l.sum + r.sum, l.len + r.len};
}

S e() {
    return {0, 0};
}

S mapping(F f, S x) {
    return {x.sum * f.a + f.b * x.len, x.len};
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
    vector<S> a(n);
    for (auto& x : a) {
        cin >> x.sum;
        x.len = 1;
    }
    poe::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            F f;
            cin >> l >> r >> f.a >> f.b;
            seg.apply(l, r, f);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r).sum << '\n';
        }
    }
}
