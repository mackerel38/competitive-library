#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"
#include "structure/lazy_segtree.hpp"

#include <bits/stdc++.h>
using namespace std;

using S = long long;
using F = long long;
constexpr long long INF = (1LL << 60);

S op(S a, S b) {
    return min(a, b);
}

S e() {
    return INF;
}

S mapping(F f, S x) {
    return x + f;
}

F composition(F f, F g) {
    return f + g;
}

F id() {
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<S> a(n);
    for (auto& x : a) cin >> x;
    poe::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long x;
            cin >> x;
            seg.apply(l, r, x);
        } else {
            cout << seg.prod(l, r) << '\n';
        }
    }
}
