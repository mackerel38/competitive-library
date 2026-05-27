#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"
#include "math/modint.hpp"
#include "structure/foldable_deque.hpp"

#include <bits/stdc++.h>
using namespace std;

using mint = poe::modint998244353;

struct affine {
    mint a, b;
};

affine op(affine l, affine r) {
    return {l.a * r.a, l.b * r.a + r.b};
}

affine e() {
    return {1, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    poe::foldable_deque<affine, op, e> deq;
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            affine f;
            cin >> f.a >> f.b;
            deq.push_front(f);
        } else if (t == 1) {
            affine f;
            cin >> f.a >> f.b;
            deq.push_back(f);
        } else if (t == 2) {
            deq.pop_front();
        } else if (t == 3) {
            deq.pop_back();
        } else {
            mint x;
            cin >> x;
            affine f = deq.fold();
            cout << f.a * x + f.b << '\n';
        }
    }
}
