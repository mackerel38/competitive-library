#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include <bits/stdc++.h>
using namespace std;

#include "structure/hashmap.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    poe::hashmap<long long, long long> mp;
    while (q--) {
        int t;
        long long k;
        cin >> t >> k;
        if (t == 0) {
            long long v;
            cin >> v;
            mp[k] = v;
        } else {
            cout << mp[k] << '\n';
        }
    }
}
