#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"
#include "structure/interval_heap.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    poe::interval_heap<int> pq;
    pq.reserve(n + q);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        pq.push(x);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int x;
            cin >> x;
            pq.push(x);
        } else if (t == 1) {
            cout << pq.pop_min() << '\n';
        } else {
            cout << pq.pop_max() << '\n';
        }
    }
}
