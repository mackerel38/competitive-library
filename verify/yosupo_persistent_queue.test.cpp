#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"
#include "structure/persistent_queue.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    vector<poe::persistent_queue<int>> versions(q);
    poe::persistent_queue<int> empty;
    auto get = [&](int t) -> const poe::persistent_queue<int>& {
        return t == -1 ? empty : versions[t];
    };
    for (int i = 0; i < q; ++i) {
        int c, t;
        cin >> c >> t;
        if (c == 0) {
            int x;
            cin >> x;
            versions[i] = get(t).push(x);
        } else {
            cout << get(t).front() << '\n';
            versions[i] = get(t).pop();
        }
    }
}
