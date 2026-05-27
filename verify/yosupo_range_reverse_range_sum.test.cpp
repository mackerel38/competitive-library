#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"
#include "structure/treap.hpp"

#include <bits/stdc++.h>
using namespace std;

struct S {
    long long sum;
    int len;
};

struct F {};

S op(S a, S b) {
    return {a.sum + b.sum, a.len + b.len};
}

S e() {
    return {0, 0};
}

S mapping(F, S x) {
    return x;
}

F composition(F, F) {
    return {};
}

F id() {
    return {};
}

bool operator==(F, F) {
    return true;
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
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            tr.reverse(l, r);
        } else {
            cout << tr.prod(l, r).sum << '\n';
        }
    }
}
