#define PROBLEM "https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum"
#include "math/modint.hpp"
#include "structure/static_rectangle_add_rectangle_sum.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    using mint = poe::modint998244353;
    int n, q;
    cin >> n >> q;
    vector<poe::static_rectangle_add_rectangle_sum<mint>::rectangle_add> adds(n);
    for (auto& e : adds) cin >> e.l >> e.d >> e.r >> e.u >> e.w;
    vector<poe::static_rectangle_add_rectangle_sum<mint>::rectangle_query> queries(q);
    for (auto& e : queries) cin >> e.l >> e.d >> e.r >> e.u;
    poe::static_rectangle_add_rectangle_sum<mint> ds(adds, queries);
    for (int i = 0; i < q; ++i) cout << ds.get(i) << '\n';
}
