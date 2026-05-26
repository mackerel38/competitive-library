#pragma once

#include <chrono>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace poe {

struct custom_hash {
    static std::uint64_t splitmix64(std::uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    std::size_t operator()(std::uint64_t x) const {
        static const std::uint64_t fixed_random =
            std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + fixed_random);
    }

    template <class T, class U>
    std::size_t operator()(const std::pair<T, U>& p) const {
        std::uint64_t x = static_cast<std::uint64_t>((*this)(p.first));
        std::uint64_t y = static_cast<std::uint64_t>((*this)(p.second));
        return splitmix64(x ^ (y + 0x9e3779b97f4a7c15 + (x << 6) + (x >> 2)));
    }
};

template <class Key, class T, class Hash = custom_hash>
using hashmap = std::unordered_map<Key, T, Hash>;

template <class Key, class Hash = custom_hash>
using hashset = std::unordered_set<Key, Hash>;

}  // namespace poe
