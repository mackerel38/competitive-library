#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace poe {

class offline_static_range_lis_query {
public:
    offline_static_range_lis_query() = default;
    explicit offline_static_range_lis_query(const std::vector<int>& p) : p_(p), n_(static_cast<int>(p.size())) {}

    int add_query(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        queries_.push_back({l, r, static_cast<int>(queries_.size())});
        return static_cast<int>(queries_.size()) - 1;
    }

    std::vector<int> solve() const {
        std::vector<int> ans(queries_.size());
        if (n_ == 0) return ans;
        std::vector<int> seaweed = make_seaweed(p_);
        std::vector<rect_query> rects;
        rects.reserve(queries_.size() * 4);
        for (auto q : queries_) {
            ans[q.id] = q.r - q.l;
            add_rect_query(rects, q.id, q.l + n_, q.r + n_, q.l, q.r);
        }
        std::sort(rects.begin(), rects.end(), [](const rect_query& a, const rect_query& b) {
            return a.x < b.x;
        });
        fenwick bit(2 * n_);
        int cur = 0;
        for (auto e : rects) {
            while (cur < e.x) {
                bit.add(seaweed[cur], 1);
                ++cur;
            }
            ans[e.id] -= e.sign * bit.sum(e.y);
        }
        return ans;
    }

private:
    struct query {
        int l, r, id;
    };

    struct rect_query {
        int x, y, id, sign;
    };

    class fenwick {
    public:
        explicit fenwick(int n = 0) : data_(n + 1, 0) {}

        void add(int p, int x) {
            for (++p; p < static_cast<int>(data_.size()); p += p & -p) data_[p] += x;
        }

        int sum(int r) const {
            int res = 0;
            for (; r > 0; r -= r & -r) res += data_[r];
            return res;
        }

    private:
        std::vector<int> data_;
    };

    static void add_rect_query(std::vector<rect_query>& rects, int id, int l, int r, int d, int u) {
        rects.push_back({r, u, id, 1});
        rects.push_back({l, u, id, -1});
        rects.push_back({r, d, id, -1});
        rects.push_back({l, d, id, 1});
    }

    class unit_monge_multiply {
    public:
        static std::vector<int> run(std::vector<int> a, std::vector<int> b) {
            int n = static_cast<int>(a.size());
            std::vector<int> b_inv(n);
            for (int i = 0; i < n; ++i) b_inv[b[i]] = i;
            b.swap(b_inv);
            std::vector<int> workspace(workspace_size(n));
            multiply(n, workspace.begin(), a.begin(), b.begin());
            workspace.resize(n);
            return workspace;
        }

    private:
        using iter = std::vector<int>::iterator;
        using const_iter = std::vector<int>::const_iterator;

        static int workspace_size(int n) {
            int ret = 0;
            while (n > 1) {
                ret += 2 * n;
                n = (n + 1) / 2;
                ret += 4 * n;
            }
            return ret + 1;
        }

        template <class F, class G>
        static void collect(int n, const_iter v, iter value, iter index, F pred, G map_value) {
            for (int i = 0; i < n; ++i) {
                if (pred(v[i])) {
                    *value++ = map_value(v[i]);
                    *index++ = i;
                }
            }
        }

        static void multiply(int n, iter workspace, const_iter a, const_iter b) {
            if (n == 1) {
                workspace[0] = 0;
                return;
            }
            iter c_row = workspace;
            workspace += n;
            iter c_col = workspace;
            workspace += n;
            auto solve_part = [&](int len, auto pred, auto map_value) {
                iter a_values = workspace;
                iter a_index = workspace + len;
                iter b_values = workspace + 2 * len;
                iter b_index = workspace + 3 * len;
                collect(n, a, a_values, a_index, pred, map_value);
                collect(n, b, b_values, b_index, pred, map_value);
                iter c = workspace + 4 * len;
                multiply(len, c, a_values, b_values);
                for (int i = 0; i < len; ++i) {
                    int row = a_index[i];
                    int col = b_index[c[i]];
                    c_row[row] = col;
                    c_col[col] = row;
                }
            };
            int mid = n / 2;
            solve_part(mid, [mid](int x) { return x < mid; }, [](int x) { return x; });
            solve_part(n - mid, [mid](int x) { return x >= mid; }, [mid](int x) { return x - mid; });

            struct delta_iter {
                int delta = 0;
                int col = 0;
            };
            int row = n;
            auto right = [&](delta_iter& it) {
                if (b[it.col] < mid) {
                    if (c_col[it.col] >= row) ++it.delta;
                } else {
                    if (c_col[it.col] < row) ++it.delta;
                }
                ++it.col;
            };
            auto up = [&](delta_iter& it) {
                if (a[row] < mid) {
                    if (c_row[row] >= it.col) --it.delta;
                } else {
                    if (c_row[row] < it.col) --it.delta;
                }
            };
            delta_iter neg, pos;
            while (row != 0) {
                while (pos.col != n) {
                    delta_iter tmp = pos;
                    right(tmp);
                    if (tmp.delta == 0) pos = tmp;
                    else break;
                }
                --row;
                up(neg);
                up(pos);
                while (neg.delta != 0) right(neg);
                if (neg.col > pos.col) c_row[row] = pos.col;
            }
        }
    };

    static std::vector<int> make_seaweed(const std::vector<int>& a) {
        int n = static_cast<int>(a.size());
        if (n == 1) return {0, 1};
        int mid = n / 2;
        std::vector<int> lo, hi, lo_pos, hi_pos;
        lo.reserve(mid);
        hi.reserve(n - mid);
        for (int i = 0; i < n; ++i) {
            if (a[i] < mid) {
                lo.push_back(a[i]);
                lo_pos.push_back(i);
            } else {
                hi.push_back(a[i] - mid);
                hi_pos.push_back(i);
            }
        }
        auto sea_lo = make_seaweed(lo);
        auto sea_hi = make_seaweed(hi);
        for (int& x : sea_lo) {
            if (x < static_cast<int>(lo.size())) x = lo_pos[x];
            else x = n + x - static_cast<int>(lo.size());
        }
        for (int& x : sea_hi) {
            if (x < static_cast<int>(hi.size())) x = hi_pos[x];
            else x = n + x - static_cast<int>(hi.size());
        }

        std::vector<int> p1(2 * n), p2(2 * n);
        for (int i = 0; i < static_cast<int>(hi.size()); ++i) p1[i] = i;
        for (int i = static_cast<int>(hi.size()); i < n; ++i) p1[i] = static_cast<int>(hi.size()) + sea_lo[i - static_cast<int>(hi.size())];
        for (int i = n; i < 2 * n; ++i) p1[i] = i - n + static_cast<int>(hi.size());

        for (int i = 0; i < static_cast<int>(hi.size()); ++i) p2[i] = sea_hi[i];
        for (int i = static_cast<int>(hi.size()); i < static_cast<int>(hi.size()) + n; ++i) p2[i] = i - static_cast<int>(hi.size());
        for (int i = static_cast<int>(hi.size()) + n; i < 2 * n; ++i) p2[i] = i;

        int li = 0, hi_i = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] < mid) p1[i + n] = sea_lo[li++ + static_cast<int>(lo.size())] + static_cast<int>(hi.size());
            else p2[i + static_cast<int>(hi.size())] = sea_hi[hi_i++ + static_cast<int>(hi.size())];
        }
        return unit_monge_multiply::run(p1, p2);
    }

    std::vector<int> p_;
    int n_ = 0;
    std::vector<query> queries_;
};

}  // namespace poe
