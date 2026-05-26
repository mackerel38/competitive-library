#pragma once

#include "math/convolution.hpp"
#include "math/modint.hpp"

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace poe {

template <class Mint>
class formal_power_series : public std::vector<Mint> {
    using base = std::vector<Mint>;

public:
    using base::base;

    formal_power_series(const std::vector<Mint>& v) : base(v) {}
    formal_power_series(std::vector<Mint>&& v) : base(std::move(v)) {}

    formal_power_series pre(int n) const {
        return formal_power_series(base(this->begin(), this->begin() + std::min(n, static_cast<int>(this->size()))));
    }

    formal_power_series rev() const {
        formal_power_series res = *this;
        std::reverse(res.begin(), res.end());
        return res;
    }

    formal_power_series& shrink() {
        while (!this->empty() && this->back() == Mint(0)) this->pop_back();
        return *this;
    }

    formal_power_series& operator+=(const formal_power_series& rhs) {
        if (this->size() < rhs.size()) this->resize(rhs.size());
        for (int i = 0; i < static_cast<int>(rhs.size()); ++i) (*this)[i] += rhs[i];
        return *this;
    }

    formal_power_series& operator-=(const formal_power_series& rhs) {
        if (this->size() < rhs.size()) this->resize(rhs.size());
        for (int i = 0; i < static_cast<int>(rhs.size()); ++i) (*this)[i] -= rhs[i];
        return *this;
    }

    formal_power_series& operator*=(const formal_power_series& rhs) {
        return *this = convolution<Mint>(*this, rhs);
    }

    formal_power_series& operator*=(const Mint& rhs) {
        for (auto& x : *this) x *= rhs;
        return *this;
    }

    formal_power_series& operator/=(const Mint& rhs) { return *this *= rhs.inv(); }

    formal_power_series operator-() const {
        formal_power_series res = *this;
        for (auto& x : res) x = -x;
        return res;
    }

    formal_power_series diff() const {
        int n = static_cast<int>(this->size());
        if (n == 0) return {};
        formal_power_series res(std::max(0, n - 1));
        for (int i = 1; i < n; ++i) res[i - 1] = (*this)[i] * i;
        return res;
    }

    formal_power_series integral() const {
        int n = static_cast<int>(this->size());
        formal_power_series res(n + 1);
        for (int i = 0; i < n; ++i) res[i + 1] = (*this)[i] / (i + 1);
        return res;
    }

    formal_power_series inv(int deg = -1) const {
        assert(!this->empty() && (*this)[0] != Mint(0));
        if (deg == -1) deg = static_cast<int>(this->size());
        formal_power_series res{(*this)[0].inv()};
        for (int m = 1; m < deg; m <<= 1) {
            formal_power_series f = pre(2 * m);
            formal_power_series g = res;
            f.resize(2 * m);
            g.resize(2 * m);
            internal::ntt(f, false);
            internal::ntt(g, false);
            for (int i = 0; i < 2 * m; ++i) f[i] = g[i] * (Mint(2) - f[i] * g[i]);
            internal::ntt(f, true);
            f.resize(2 * m);
            res = f.pre(std::min(2 * m, deg));
        }
        return res.pre(deg);
    }

    formal_power_series log(int deg = -1) const {
        assert(!this->empty() && (*this)[0] == Mint(1));
        if (deg == -1) deg = static_cast<int>(this->size());
        return (diff() * inv(deg)).pre(deg - 1).integral().pre(deg);
    }

    formal_power_series exp(int deg = -1) const {
        assert(this->empty() || (*this)[0] == Mint(0));
        if (deg == -1) deg = static_cast<int>(this->size());
        formal_power_series res(deg);
        if (deg == 0) return res;
        res[0] = 1;
        for (int n = 1; n < deg; ++n) {
            Mint sum = 0;
            for (int i = 1; i <= n && i < static_cast<int>(this->size()); ++i) {
                sum += Mint(i) * (*this)[i] * res[n - i];
            }
            res[n] = sum / n;
        }
        return res;
    }

    formal_power_series pow(long long k, int deg = -1) const {
        if (deg == -1) deg = static_cast<int>(this->size());
        if (k == 0) {
            formal_power_series res(deg);
            if (deg) res[0] = 1;
            return res;
        }
        int n = static_cast<int>(this->size());
        int lz = 0;
        while (lz < n && (*this)[lz] == Mint(0)) ++lz;
        if (lz == n || static_cast<long long>(lz) * k >= deg) return formal_power_series(deg);
        Mint c = (*this)[lz];
        formal_power_series f(base(this->begin() + lz, this->end()));
        f /= c;
        formal_power_series g = (f.log(deg - lz * k) * Mint(k)).exp(deg - lz * k);
        g *= c.pow(k);
        formal_power_series res(deg);
        for (int i = 0; i < static_cast<int>(g.size()) && i + lz * k < deg; ++i) {
            res[i + lz * k] = g[i];
        }
        return res;
    }

    friend formal_power_series operator+(formal_power_series lhs, const formal_power_series& rhs) { return lhs += rhs; }
    friend formal_power_series operator-(formal_power_series lhs, const formal_power_series& rhs) { return lhs -= rhs; }
    friend formal_power_series operator*(formal_power_series lhs, const formal_power_series& rhs) { return lhs *= rhs; }
    friend formal_power_series operator*(formal_power_series lhs, const Mint& rhs) { return lhs *= rhs; }
    friend formal_power_series operator*(const Mint& lhs, formal_power_series rhs) { return rhs *= lhs; }
    friend formal_power_series operator/(formal_power_series lhs, const Mint& rhs) { return lhs /= rhs; }
};

}  // namespace poe
