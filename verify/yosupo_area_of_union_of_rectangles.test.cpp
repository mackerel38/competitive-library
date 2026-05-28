#define PROBLEM "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"
#include "structure/area_of_union_of_rectangles.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<array<long long, 4>> rects(n);
    for (auto& e : rects) cin >> e[0] >> e[1] >> e[2] >> e[3];
    cout << poe::area_of_union_of_rectangles(rects) << '\n';
}
