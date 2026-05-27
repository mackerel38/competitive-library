#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"
#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "structure/treap.hpp"

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
    poe::treap<S, op, e, F, mapping, composition, id> tr(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i;
            mint x;
            cin >> i >> x;
            tr.insert(i, {x, 1});
        } else if (t == 1) {
            int i;
            cin >> i;
            tr.erase(i);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            tr.reverse(l, r);
        } else if (t == 3) {
            int l, r;
            F f;
            cin >> l >> r >> f.a >> f.b;
            tr.apply(l, r, f);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tr.prod(l, r).sum << '\n';
        }
    }
}
