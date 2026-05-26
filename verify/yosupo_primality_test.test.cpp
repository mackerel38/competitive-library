#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include "math/prime.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    while (q--) {
        long long n;
        std::cin >> n;
        std::cout << (poe::is_prime(n) ? "Yes" : "No") << '\n';
    }
}
