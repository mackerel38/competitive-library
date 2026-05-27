#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "structure/li_chao_tree.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<pair<long long, long long>> initial(n);
    for (auto& [a, b] : initial) cin >> a >> b;
    struct query {
        int type;
        long long a, b, x;
    };
    vector<query> queries;
    vector<long long> xs;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            long long a, b;
            cin >> a >> b;
            queries.push_back({t, a, b, 0});
        } else {
            long long x;
            cin >> x;
            xs.push_back(x);
            queries.push_back({t, 0, 0, x});
        }
    }
    poe::li_chao_tree<long long> cht(xs);
    for (auto [a, b] : initial) cht.add_line(a, b);
    for (auto [type, a, b, x] : queries) {
        if (type == 0) cht.add_line(a, b);
        else cout << cht.get_min(x) << '\n';
    }
}
