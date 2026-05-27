#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"
#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "structure/simple_treap.hpp"
#include "structure/treap.hpp"

using mint = poe::modint998244353;

struct S {
    mint sum;
    int len;
};

struct F {
    mint a, b;
};

S op(S l, S r) {
    return {l.sum + r.sum, l.len + r.len};
}

S e() {
    return {0, 0};
}

S mapping(F f, S x) {
    return {x.sum * f.a + f.b * x.len, x.len};
}

F composition(F f, F g) {
    return {g.a * f.a, g.b * f.a + f.b};
}

F id() {
    return {1, 0};
}

int main() {
    {
        poe::random_engine rng(123456789);
        poe::simple_treap<int> tr;
        vector<int> expected;
        for (int step = 0; step < 20000; ++step) {
            int type = rng.uniform_int(0, 6);
            if (expected.empty()) type = 0;
            if (type == 0) {
                int p = rng.uniform_int(0, static_cast<int>(expected.size()) + 1);
                int x = rng.uniform_int(-1000000, 1000001);
                tr.insert(p, x);
                expected.insert(expected.begin() + p, x);
            } else if (type == 1) {
                int p = rng.uniform_int(0, static_cast<int>(expected.size()));
                int a = tr.erase(p);
                int b = expected[p];
                expected.erase(expected.begin() + p);
                assert(a == b);
            } else if (type == 2) {
                int p = rng.uniform_int(0, static_cast<int>(expected.size()));
                assert(tr.get(p) == expected[p]);
            } else if (type == 3) {
                int p = rng.uniform_int(0, static_cast<int>(expected.size()));
                int x = rng.uniform_int(-1000000, 1000001);
                tr.set(p, x);
                expected[p] = x;
            } else if (type == 4) {
                int p = rng.uniform_int(0, static_cast<int>(expected.size()) + 1);
                auto right = tr.split_off(p);
                vector<int> left_expected(expected.begin(), expected.begin() + p);
                vector<int> right_expected(expected.begin() + p, expected.end());
                assert(tr.to_vector() == left_expected);
                assert(right.to_vector() == right_expected);
                tr.merge_back(right);
            } else {
                assert(tr.to_vector() == expected);
            }
            assert(tr.size() == static_cast<int>(expected.size()));
        }
        assert(tr.to_vector() == expected);
    }
    {
        vector<int> sorted;
        for (int i = 0; i < 200; ++i) {
            sorted.push_back(i / 3);
        }
        poe::simple_treap<int> tr(sorted);
        for (int x = -3; x <= 70; ++x) {
            int lb = lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
            int ub = upper_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
            assert(tr.lower_bound(x) == lb);
            assert(tr.upper_bound(x) == ub);
            assert(tr.count_lt(x) == lb);
            assert(tr.count_le(x) == ub);
            assert(tr.count_ge(x) == static_cast<int>(sorted.size()) - lb);
            assert(tr.count_gt(x) == static_cast<int>(sorted.size()) - ub);
            assert(tr.contains_sorted(x) == binary_search(sorted.begin(), sorted.end(), x));
        }
        for (int i = 0; i < static_cast<int>(sorted.size()); ++i) {
            assert(tr.kth(i) == sorted[i]);
        }
    }
    {
        vector<S> a;
        for (int i = 1; i <= 5; ++i) a.push_back({i, 1});
        poe::treap<S, op, e, F, mapping, composition, id> tr(a);
        auto ok6 = [](S x) { return x.sum.val() <= 6; };
        auto ok9 = [](S x) { return x.sum.val() <= 9; };
        assert(tr.max_right(0, ok6) == 3);
        assert(tr.min_left(5, ok9) == 3);
        assert(tr.kth(2).sum == mint(3));
    }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<S> a(n);
    for (auto& x : a) {
        cin >> x.sum;
        x.len = 1;
    }
    poe::treap<S, op, e, F, mapping, composition, id> tr(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i;
            mint x;
            cin >> i >> x;
            tr.insert(i, {x, 1});
        } else if (t == 1) {
            int i;
            cin >> i;
            tr.erase(i);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            tr.reverse(l, r);
        } else if (t == 3) {
            int l, r;
            F f;
            cin >> l >> r >> f.a >> f.b;
            tr.apply(l, r, f);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tr.prod(l, r).sum << '\n';
        }
    }
}
