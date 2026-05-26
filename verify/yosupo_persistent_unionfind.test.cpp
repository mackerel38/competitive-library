#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"
#include <bits/stdc++.h>
using namespace std;

#include "structure/rollback_dsu.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> type(q + 1), u(q + 1), v(q + 1);
    vector<vector<int>> children(q + 1);
    for (int i = 1; i <= q; ++i) {
        int k;
        cin >> type[i] >> k >> u[i] >> v[i];
        children[k + 1].push_back(i);
    }
    poe::rollback_dsu uf(n);
    vector<int> ans(q + 1);
    auto dfs = [&](auto&& self, int now) -> void {
        int snap = uf.snapshot();
        if (type[now] == 0) uf.merge(u[now], v[now]);
        if (type[now] == 1) ans[now] = uf.same(u[now], v[now]);
        for (int to : children[now]) self(self, to);
        uf.rollback(snap);
    };
    dfs(dfs, 0);
    for (int i = 1; i <= q; ++i) {
        if (type[i] == 1) cout << ans[i] << '\n';
    }
}
