#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "structure/ordered_set.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    string s;
    cin >> n >> q >> s;
    poe::ordered_set<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') st.insert(i);
    }
    while (q--) {
        int t, k;
        cin >> t >> k;
        if (t == 0) {
            st.insert(k);
        } else if (t == 1) {
            st.erase(k);
        } else if (t == 2) {
            cout << st.contains(k) << '\n';
        } else if (t == 3) {
            int id = st.count_lt(k);
            cout << (id == st.size() ? -1 : st.kth(id)) << '\n';
        } else {
            int id = st.count_le(k);
            cout << (id == 0 ? -1 : st.kth(id - 1)) << '\n';
        }
    }
}
