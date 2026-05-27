#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
#include "structure/ordered_set.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    poe::ordered_set<int> st;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        st.insert(a);
    }
    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 0) {
            st.insert(x);
        } else if (t == 1) {
            st.erase(x);
        } else if (t == 2) {
            if (x <= 0 || x > st.size()) cout << -1 << '\n';
            else cout << st.kth(x - 1) << '\n';
        } else if (t == 3) {
            cout << st.count_le(x) << '\n';
        } else if (t == 4) {
            int k = st.count_le(x);
            cout << (k == 0 ? -1 : st.kth(k - 1)) << '\n';
        } else {
            int k = st.count_lt(x);
            cout << (k == st.size() ? -1 : st.kth(k)) << '\n';
        }
    }
}
