#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class T>
class matrix {
public:
    matrix() = default;
    matrix(int h, int w, T value = T()) : a_(h, std::vector<T>(w, value)) {}
    explicit matrix(std::vector<std::vector<T>> a) : a_(std::move(a)) {}

    static matrix identity(int n) {
        matrix e(n, n);
        for (int i = 0; i < n; ++i) e[i][i] = T(1);
        return e;
    }

    int height() const { return static_cast<int>(a_.size()); }
    int width() const { return a_.empty() ? 0 : static_cast<int>(a_[0].size()); }
    const std::vector<T>& operator[](int i) const { return a_[i]; }
    std::vector<T>& operator[](int i) { return a_[i]; }

    matrix& operator+=(const matrix& rhs) {
        assert(height() == rhs.height() && width() == rhs.width());
        for (int i = 0; i < height(); ++i) {
            for (int j = 0; j < width(); ++j) a_[i][j] += rhs[i][j];
        }
        return *this;
    }

    matrix& operator-=(const matrix& rhs) {
        assert(height() == rhs.height() && width() == rhs.width());
        for (int i = 0; i < height(); ++i) {
            for (int j = 0; j < width(); ++j) a_[i][j] -= rhs[i][j];
        }
        return *this;
    }

    matrix& operator*=(const matrix& rhs) { return *this = *this * rhs; }

    matrix pow(long long n) const {
        assert(n >= 0);
        assert(height() == width());
        matrix x = *this, r = identity(height());
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }

    friend matrix operator+(matrix lhs, const matrix& rhs) { return lhs += rhs; }
    friend matrix operator-(matrix lhs, const matrix& rhs) { return lhs -= rhs; }
    friend matrix operator*(const matrix& lhs, const matrix& rhs) {
        assert(lhs.width() == rhs.height());
        matrix res(lhs.height(), rhs.width());
        for (int i = 0; i < lhs.height(); ++i) {
            for (int k = 0; k < lhs.width(); ++k) {
                for (int j = 0; j < rhs.width(); ++j) {
                    res[i][j] += lhs[i][k] * rhs[k][j];
                }
            }
        }
        return res;
    }

private:
    std::vector<std::vector<T>> a_;
};

}  // namespace poe

