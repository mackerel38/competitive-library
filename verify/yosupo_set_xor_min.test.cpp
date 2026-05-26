#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"
#include <bits/stdc++.h>
using namespace std;

#include "structure/binary_trie.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    poe::binary_trie<unsigned int, 30> trie;
    while (q--) {
        int t;
        unsigned int x;
        cin >> t >> x;
        if (t == 0) {
            if (!trie.contains(x)) trie.insert(x);
        } else if (t == 1) {
            if (trie.contains(x)) trie.erase(x);
        } else {
            cout << (trie.min_element(x) ^ x) << '\n';
        }
    }
}
