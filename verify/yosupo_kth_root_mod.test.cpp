#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_mod"
#include <bits/stdc++.h>
using namespace std;

#include "math/kth_root_mod.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    map<long long, poe::prime_mod_kth_root_solver> solvers;
    while (t--) {
        long long k, y, p;
        cin >> k >> y >> p;
        auto it = solvers.find(p);
        if (it == solvers.end()) it = solvers.emplace(p, poe::prime_mod_kth_root_solver(p)).first;
        cout << it->second.kth_root(y, k) << '\n';
    }
}
