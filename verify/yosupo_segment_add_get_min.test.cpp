#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"
#include "structure/li_chao_tree.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    struct segment {
        long long l, r, a, b;
    };
    vector<segment> initial(n);
    vector<long long> xs;
    for (auto& e : initial) {
        cin >> e.l >> e.r >> e.a >> e.b;
        xs.push_back(e.l);
        xs.push_back(e.r);
    }
    struct query {
        int type;
        long long l, r, a, b, x;
    };
    vector<query> queries;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            long long l, r, a, b;
            cin >> l >> r >> a >> b;
            xs.push_back(l);
            xs.push_back(r);
            queries.push_back({t, l, r, a, b, 0});
        } else {
            long long x;
            cin >> x;
            xs.push_back(x);
            queries.push_back({t, 0, 0, 0, 0, x});
        }
    }
    poe::li_chao_tree<long long> cht(xs);
    for (auto [l, r, a, b] : initial) cht.add_segment(a, b, l, r);
    const long long inf = numeric_limits<long long>::max() / 4;
    for (auto [type, l, r, a, b, x] : queries) {
        if (type == 0) {
            cht.add_segment(a, b, l, r);
        } else {
            long long ans = cht.get_min(x);
            if (ans == inf) cout << "INFINITY\n";
            else cout << ans << '\n';
        }
    }
}
