#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "math/convolution.hpp"

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<poe::modint998244353> a(n), b(m);
    for (auto& x : a) std::cin >> x;
    for (auto& x : b) std::cin >> x;

    auto c = poe::convolution(a, b);
    for (int i = 0; i < static_cast<int>(c.size()); ++i) {
        if (i) std::cout << ' ';
        std::cout << c[i];
    }
    std::cout << '\n';
}
