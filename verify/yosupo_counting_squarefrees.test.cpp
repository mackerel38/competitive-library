#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"
#include <bits/stdc++.h>
using namespace std;

#include "math/square_free_count.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    cout << poe::count_square_free(n) << '\n';
}
