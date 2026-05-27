#define PROBLEM "https://judge.yosupo.jp/problem/deque"
#include "structure/simple_treap.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    poe::simple_treap<int> deq;
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int x;
            cin >> x;
            deq.insert(0, x);
        } else if (t == 1) {
            int x;
            cin >> x;
            deq.insert(deq.size(), x);
        } else if (t == 2) {
            deq.erase(0);
        } else if (t == 3) {
            deq.erase(deq.size() - 1);
        } else {
            int x;
            cin >> x;
            cout << deq.get(x) << '\n';
        }
    }
}
