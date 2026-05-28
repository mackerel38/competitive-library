#pragma once

#include <cassert>
#include <cstdlib>
#include <utility>

namespace poe {

struct gaussian_integer {
    long long real;
    long long imag;

    gaussian_integer(long long r = 0, long long i = 0) : real(r), imag(i) {}

    long long norm() const { return real * real + imag * imag; }

    gaussian_integer conj() const { return {real, -imag}; }

    gaussian_integer& operator+=(const gaussian_integer& rhs) {
        real += rhs.real;
        imag += rhs.imag;
        return *this;
    }

    gaussian_integer& operator-=(const gaussian_integer& rhs) {
        real -= rhs.real;
        imag -= rhs.imag;
        return *this;
    }

    gaussian_integer& operator*=(const gaussian_integer& rhs) {
        long long r = real * rhs.real - imag * rhs.imag;
        long long i = real * rhs.imag + imag * rhs.real;
        real = r;
        imag = i;
        return *this;
    }

    friend gaussian_integer operator+(gaussian_integer lhs, const gaussian_integer& rhs) { return lhs += rhs; }
    friend gaussian_integer operator-(gaussian_integer lhs, const gaussian_integer& rhs) { return lhs -= rhs; }
    friend gaussian_integer operator*(gaussian_integer lhs, const gaussian_integer& rhs) { return lhs *= rhs; }
    friend bool operator==(const gaussian_integer& lhs, const gaussian_integer& rhs) {
        return lhs.real == rhs.real && lhs.imag == rhs.imag;
    }
    friend bool operator!=(const gaussian_integer& lhs, const gaussian_integer& rhs) { return !(lhs == rhs); }
};

long long div_round_nearest(long long x, long long y) {
    assert(y > 0);
    if (x >= 0) return (x + y / 2) / y;
    return -((-x + y / 2) / y);
}

gaussian_integer gaussian_div_round(gaussian_integer a, gaussian_integer b) {
    assert(b.real != 0 || b.imag != 0);
    long long n = b.norm();
    gaussian_integer c = a * b.conj();
    return {div_round_nearest(c.real, n), div_round_nearest(c.imag, n)};
}

gaussian_integer gaussian_gcd(gaussian_integer a, gaussian_integer b) {
    while (b.real != 0 || b.imag != 0) {
        gaussian_integer q = gaussian_div_round(a, b);
        gaussian_integer r = a - q * b;
        a = b;
        b = r;
    }
    if (a.real < 0 || (a.real == 0 && a.imag < 0)) {
        a.real = -a.real;
        a.imag = -a.imag;
    }
    return a;
}

}  // namespace poe

