#pragma once

#include <algorithm>
#include <cstdint>

namespace poe {

namespace nim_product_internal {

using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

struct calc8 {
    u16 dp[1 << 8][1 << 8];

    calc8() : dp() {
        dp[1][1] = 1;
        for (int e = 1; e <= 3; ++e) {
            int p = 1 << e, q = p >> 1;
            u16 ep = static_cast<u16>(1u << p);
            u16 eq = static_cast<u16>(1u << q);
            for (u16 i = 0; i < ep; ++i) {
                for (u16 j = i; j < ep; ++j) {
                    if (i < eq && j < eq) continue;
                    if (std::min(i, j) <= 1u) {
                        dp[i][j] = dp[j][i] = i * j;
                        continue;
                    }
                    u16 iu = i >> q, il = i & (eq - 1);
                    u16 ju = j >> q, jl = j & (eq - 1);
                    u16 u = dp[iu][ju], l = dp[il][jl];
                    u16 ul = dp[iu ^ il][ju ^ jl];
                    u16 uq = dp[u][eq >> 1];
                    dp[i][j] = dp[j][i] = static_cast<u16>(((ul ^ l) << q) ^ uq ^ l);
                }
            }
        }
    }
};

inline const calc8 c8;

struct calc16 {
    static constexpr u16 proot = 10279;
    static constexpr u32 ppoly = 92191;
    static constexpr int order = 65535;

    u16 base[16];
    u16 exp[(1 << 18) + 100];
    int log[1 << 16];

    u16 d(u32 x) const { return static_cast<u16>((x << 1) ^ (x < 32768u ? 0 : ppoly)); }

    u16 naive(u16 i, u16 j) const {
        if (std::min(i, j) <= 1u) return i * j;
        u16 q = 8, eq = 1u << 8;
        u16 iu = i >> q, il = i & (eq - 1);
        u16 ju = j >> q, jl = j & (eq - 1);
        u16 u = c8.dp[iu][ju], l = c8.dp[il][jl];
        u16 ul = c8.dp[iu ^ il][ju ^ jl];
        u16 uq = c8.dp[u][eq >> 1];
        return static_cast<u16>(((ul ^ l) << q) ^ uq ^ l);
    }

    calc16() : base(), exp(), log() {
        base[0] = 1;
        for (int i = 1; i < 16; ++i) base[i] = naive(base[i - 1], proot);
        exp[0] = 1;
        for (int i = 1; i < order; ++i) exp[i] = d(exp[i - 1]);

        u16* pre = exp + order + 1;
        pre[0] = 0;
        for (int b = 0; b < 16; ++b) {
            int is = 1 << b, ie = is << 1;
            for (int i = is; i < ie; ++i) pre[i] = pre[i - is] ^ base[b];
        }
        for (int i = 0; i < order; ++i) {
            exp[i] = pre[exp[i]];
            log[exp[i]] = i;
        }
        int ie = 2 * order + 30;
        for (int i = order; i < ie; ++i) exp[i] = exp[i - order];
        log[0] = ie + 1;
    }

    u16 prod(u16 i, u16 j) const { return exp[log[i] + log[j]]; }
    u16 hprod(u16 i, u16 j) const { return exp[log[i] + log[j] + 3]; }
    u16 h(u16 i) const { return exp[log[i] + 3]; }
    u16 h2(u16 i) const { return exp[log[i] + 6]; }
};

inline const calc16 c16;

inline u32 product32(u32 a, u32 b) {
    u16 au = a >> 16, al = a & 65535;
    u16 bu = b >> 16, bl = b & 65535;
    u16 l = c16.prod(al, bl);
    u16 ul = c16.prod(au ^ al, bu ^ bl);
    u16 uq = c16.hprod(au, bu);
    return (u32(ul ^ l) << 16) ^ uq ^ l;
}

inline u32 h(u32 a) {
    u16 au = a >> 16, al = a & 65535;
    return (u32(c16.h(au ^ al)) << 16) ^ c16.h2(au);
}

inline u64 product64(u64 a, u64 b) {
    u32 au = a >> 32, al = a & u32(-1);
    u32 bu = b >> 32, bl = b & u32(-1);
    u32 l = product32(al, bl);
    u32 ul = product32(au ^ al, bu ^ bl);
    u32 uq = h(product32(au, bu));
    return (u64(ul ^ l) << 32) ^ uq ^ l;
}

}  // namespace nim_product_internal

std::uint64_t nim_product(std::uint64_t a, std::uint64_t b) {
    return nim_product_internal::product64(a, b);
}

}  // namespace poe
