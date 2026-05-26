#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "structure/swag.hpp"

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

    int q;
    cin >> q;
    poe::swag<Affine, op, e> que;
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            Affine f;
            cin >> f.a >> f.b;
            que.push(f);
        } else if (t == 1) {
            que.pop();
        } else {
            mint x;
            cin >> x;
            Affine f = que.fold();
            cout << f.a * x + f.b << '\n';
        }
    }
}
