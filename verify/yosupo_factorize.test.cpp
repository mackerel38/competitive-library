#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include "math/prime.hpp"

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    while (q--) {
        long long n;
        std::cin >> n;
        std::vector<long long> primes;
        for (auto [p, e] : poe::factorize(n)) {
            while (e--) primes.push_back(p);
        }
        std::cout << primes.size();
        for (long long p : primes) std::cout << ' ' << p;
        std::cout << '\n';
    }
}
