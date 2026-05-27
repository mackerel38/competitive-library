#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iterator>
#include <limits>
#include <random>

namespace poe {

class random_engine {
public:
    using result_type = std::uint64_t;

    random_engine() : state_(make_seed()) {}
    explicit random_engine(std::uint64_t seed) : state_(seed) {}

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    result_type operator()() { return splitmix64(state_); }

    std::uint64_t uniform_u64(std::uint64_t l, std::uint64_t r) {
        assert(l < r);
        std::uint64_t width = r - l;
        std::uint64_t limit = max() - max() % width;
        std::uint64_t x = operator()();
        while (x >= limit) x = operator()();
        return l + x % width;
    }

    int uniform_int(int l, int r) {
        assert(l < r);
        return static_cast<int>(static_cast<long long>(l) + uniform_u64(0, static_cast<std::uint64_t>(r - l)));
    }

    long long uniform_ll(long long l, long long r) {
        assert(l < r);
        std::uint64_t width = static_cast<std::uint64_t>(static_cast<__int128>(r) - l);
        return l + static_cast<long long>(uniform_u64(0, width));
    }

    double uniform_real() {
        constexpr double inv = 1.0 / static_cast<double>(std::uint64_t(1) << 53);
        return static_cast<double>(operator()() >> 11) * inv;
    }

    template <class RandomIt>
    void shuffle(RandomIt first, RandomIt last) {
        using diff_t = typename std::iterator_traits<RandomIt>::difference_type;
        for (diff_t i = last - first; i > 1; --i) {
            diff_t j = static_cast<diff_t>(uniform_u64(0, static_cast<std::uint64_t>(i)));
            std::iter_swap(first + (i - 1), first + j);
        }
    }

private:
    static std::uint64_t splitmix64(std::uint64_t& x) {
        std::uint64_t z = (x += 0x9e3779b97f4a7c15ULL);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        return z ^ (z >> 31);
    }

    static std::uint64_t make_seed() {
        std::uint64_t seed = static_cast<std::uint64_t>(
            std::chrono::steady_clock::now().time_since_epoch().count());
        seed ^= static_cast<std::uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) << 1;
        seed ^= reinterpret_cast<std::uintptr_t>(&seed);
        std::random_device rd;
        seed ^= static_cast<std::uint64_t>(rd()) << 32;
        seed ^= static_cast<std::uint64_t>(rd());
        return seed;
    }

    std::uint64_t state_;
};

inline random_engine& global_random_engine() {
    static random_engine engine;
    return engine;
}

inline std::uint64_t rand_u64() {
    return global_random_engine()();
}

inline int rand_int(int l, int r) {
    return global_random_engine().uniform_int(l, r);
}

inline long long rand_ll(long long l, long long r) {
    return global_random_engine().uniform_ll(l, r);
}

}  // namespace poe
