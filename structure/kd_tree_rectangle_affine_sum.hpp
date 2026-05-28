#pragma once

#include <algorithm>
#include <cassert>
#include <limits>
#include <map>
#include <vector>

namespace poe {

template <class T>
class kd_tree_rectangle_affine_sum {
public:
    struct point {
        long long x, y;
        T w;
        bool active = true;
    };
    struct affine {
        T a;
        T b;
    };

    kd_tree_rectangle_affine_sum() = default;
    explicit kd_tree_rectangle_affine_sum(const std::vector<point>& points) : points_(points) {
        std::vector<long long> xs, ys;
        xs.reserve(points_.size());
        ys.reserve(points_.size());
        for (const auto& p : points_) {
            xs.push_back(p.x);
            ys.push_back(p.y);
        }
        std::sort(xs.begin(), xs.end());
        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
        std::sort(ys.begin(), ys.end());
        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
        constexpr int small_limit = 700;
        if (!points_.empty() && static_cast<int>(ys.size()) <= small_limit && ys.size() <= xs.size()) {
            mode_ = mode::rows;
            build_groups(false, ys);
            return;
        }
        if (!points_.empty() && static_cast<int>(xs.size()) <= small_limit) {
            mode_ = mode::cols;
            build_groups(true, xs);
            return;
        }
        mode_ = mode::kd;
        std::vector<int> ids(points_.size());
        for (int i = 0; i < static_cast<int>(ids.size()); ++i) ids[i] = i;
        nodes_.reserve(points_.size());
        parent_.reserve(points_.size());
        leaf_.assign(points_.size(), -1);
        root_ = build(ids, 0, static_cast<int>(ids.size()), 0);
    }

    int size() const { return static_cast<int>(points_.size()); }

    void activate(int id, T w) {
        assert(0 <= id && id < size());
        points_[id].active = true;
        if (mode_ != mode::kd) {
            groups_[group_id_[id]].set(point_pos_[id], w);
            return;
        }
        set_weight(id, w);
    }

    void set(int id, T w) {
        assert(0 <= id && id < size());
        points_[id].active = true;
        if (mode_ != mode::kd) {
            groups_[group_id_[id]].set(point_pos_[id], w);
            return;
        }
        set_weight(id, w);
    }

    T sum(long long l, long long d, long long r, long long u) {
        if (mode_ == mode::rows) return groups_sum(d, u, l, r);
        if (mode_ == mode::cols) return groups_sum(l, r, d, u);
        return sum(root_, l, d, r, u);
    }

    void apply(long long l, long long d, long long r, long long u, affine f) {
        if (mode_ == mode::rows) {
            groups_apply(d, u, l, r, f);
            return;
        }
        if (mode_ == mode::cols) {
            groups_apply(l, r, d, u, f);
            return;
        }
        apply(root_, l, d, r, u, f);
    }

private:
    enum class mode { kd, rows, cols };

    struct group_entry {
        long long coord;
        int id;
        point p;
    };

    struct group {
        int n = 0;
        std::vector<long long> coord;
        std::vector<int> active_count;
        std::vector<T> sum;
        std::vector<affine> lazy;

        explicit group(const std::vector<group_entry>& entries) {
            n = static_cast<int>(entries.size());
            coord.reserve(n);
            active_count.assign(n * 4, 0);
            sum.assign(n * 4, T{});
            lazy.assign(n * 4, {T(1), T(0)});
            for (const auto& e : entries) coord.push_back(e.coord);
            build(entries, 1, 0, n);
        }

        void set(int pos, T value) { set(1, 0, n, pos, value); }

        T range_sum(long long l, long long r) {
            int ql = static_cast<int>(std::lower_bound(coord.begin(), coord.end(), l) - coord.begin());
            int qr = static_cast<int>(std::lower_bound(coord.begin(), coord.end(), r) - coord.begin());
            return range_sum(1, 0, n, ql, qr);
        }

        void range_apply(long long l, long long r, affine f) {
            int ql = static_cast<int>(std::lower_bound(coord.begin(), coord.end(), l) - coord.begin());
            int qr = static_cast<int>(std::lower_bound(coord.begin(), coord.end(), r) - coord.begin());
            range_apply(1, 0, n, ql, qr, f);
        }

    private:
        static affine compose(affine f, affine g) {
            return {f.a * g.a, f.a * g.b + f.b};
        }

        void build(const std::vector<group_entry>& entries, int k, int l, int r) {
            if (r - l == 1) {
                if (entries[l].p.active) {
                    active_count[k] = 1;
                    sum[k] = entries[l].p.w;
                }
                return;
            }
            int m = (l + r) >> 1;
            build(entries, k << 1, l, m);
            build(entries, k << 1 | 1, m, r);
            pull(k);
        }

        void all_apply(int k, affine f) {
            if (active_count[k] == 0) return;
            sum[k] = f.a * sum[k] + f.b * T(active_count[k]);
            lazy[k] = compose(f, lazy[k]);
        }

        void push(int k) {
            affine f = lazy[k];
            if (f.a == T(1) && f.b == T(0)) return;
            all_apply(k << 1, f);
            all_apply(k << 1 | 1, f);
            lazy[k] = {T(1), T(0)};
        }

        void pull(int k) {
            active_count[k] = active_count[k << 1] + active_count[k << 1 | 1];
            sum[k] = sum[k << 1] + sum[k << 1 | 1];
        }

        void set(int k, int l, int r, int pos, T value) {
            if (r - l == 1) {
                active_count[k] = 1;
                sum[k] = value;
                lazy[k] = {T(1), T(0)};
                return;
            }
            push(k);
            int m = (l + r) >> 1;
            if (pos < m) set(k << 1, l, m, pos, value);
            else set(k << 1 | 1, m, r, pos, value);
            pull(k);
        }

        T range_sum(int k, int l, int r, int ql, int qr) {
            if (qr <= l || r <= ql || active_count[k] == 0) return T{};
            if (ql <= l && r <= qr) return sum[k];
            push(k);
            int m = (l + r) >> 1;
            return range_sum(k << 1, l, m, ql, qr) + range_sum(k << 1 | 1, m, r, ql, qr);
        }

        void range_apply(int k, int l, int r, int ql, int qr, affine f) {
            if (qr <= l || r <= ql || active_count[k] == 0) return;
            if (ql <= l && r <= qr) {
                all_apply(k, f);
                return;
            }
            push(k);
            int m = (l + r) >> 1;
            range_apply(k << 1, l, m, ql, qr, f);
            range_apply(k << 1 | 1, m, r, ql, qr, f);
            pull(k);
        }
    };

    struct node {
        int left = -1;
        int right = -1;
        int point_id = -1;
        long long min_x, max_x, min_y, max_y;
        int active_count = 0;
        T sum{};
        affine lazy{T(1), T(0)};
    };

    static affine compose(affine f, affine g) {
        return {f.a * g.a, f.a * g.b + f.b};
    }

    void build_groups(bool use_x_as_group, const std::vector<long long>& keys) {
        group_keys_ = keys;
        std::map<long long, std::vector<group_entry>> buckets;
        for (int i = 0; i < size(); ++i) {
            long long key = use_x_as_group ? points_[i].x : points_[i].y;
            long long value = use_x_as_group ? points_[i].y : points_[i].x;
            buckets[key].push_back({value, i, points_[i]});
        }
        group_id_.assign(size(), -1);
        point_pos_.assign(size(), -1);
        groups_.reserve(group_keys_.size());
        for (int gid = 0; gid < static_cast<int>(group_keys_.size()); ++gid) {
            auto& entries = buckets[group_keys_[gid]];
            std::sort(entries.begin(), entries.end(), [](const auto& a, const auto& b) {
                return a.coord != b.coord ? a.coord < b.coord : a.id < b.id;
            });
            for (int pos = 0; pos < static_cast<int>(entries.size()); ++pos) {
                group_id_[entries[pos].id] = gid;
                point_pos_[entries[pos].id] = pos;
            }
            groups_.push_back(group(entries));
        }
    }

    T groups_sum(long long kl, long long kr, long long vl, long long vr) {
        T res{};
        int gl = static_cast<int>(std::lower_bound(group_keys_.begin(), group_keys_.end(), kl) - group_keys_.begin());
        int gr = static_cast<int>(std::lower_bound(group_keys_.begin(), group_keys_.end(), kr) - group_keys_.begin());
        for (int i = gl; i < gr; ++i) res += groups_[i].range_sum(vl, vr);
        return res;
    }

    void groups_apply(long long kl, long long kr, long long vl, long long vr, affine f) {
        int gl = static_cast<int>(std::lower_bound(group_keys_.begin(), group_keys_.end(), kl) - group_keys_.begin());
        int gr = static_cast<int>(std::lower_bound(group_keys_.begin(), group_keys_.end(), kr) - group_keys_.begin());
        for (int i = gl; i < gr; ++i) groups_[i].range_apply(vl, vr, f);
    }

    int build(std::vector<int>& ids, int l, int r, int depth) {
        if (l == r) return -1;
        int k = static_cast<int>(nodes_.size());
        nodes_.push_back({});
        parent_.push_back(-1);
        nodes_[k].min_x = nodes_[k].min_y = std::numeric_limits<long long>::max();
        nodes_[k].max_x = nodes_[k].max_y = std::numeric_limits<long long>::min();
        for (int i = l; i < r; ++i) {
            auto p = points_[ids[i]];
            nodes_[k].min_x = std::min(nodes_[k].min_x, p.x);
            nodes_[k].max_x = std::max(nodes_[k].max_x, p.x);
            nodes_[k].min_y = std::min(nodes_[k].min_y, p.y);
            nodes_[k].max_y = std::max(nodes_[k].max_y, p.y);
        }
        if (r - l == 1) {
            nodes_[k].point_id = ids[l];
            leaf_[ids[l]] = k;
            if (points_[ids[l]].active) {
                nodes_[k].active_count = 1;
                nodes_[k].sum = points_[ids[l]].w;
            }
            return k;
        }
        bool split_x = (depth % 2 == 0);
        if (nodes_[k].min_x == nodes_[k].max_x) split_x = false;
        if (nodes_[k].min_y == nodes_[k].max_y) split_x = true;
        int m = (l + r) >> 1;
        std::nth_element(ids.begin() + l, ids.begin() + m, ids.begin() + r, [&](int a, int b) {
            if (split_x) return points_[a].x != points_[b].x ? points_[a].x < points_[b].x : points_[a].y < points_[b].y;
            return points_[a].y != points_[b].y ? points_[a].y < points_[b].y : points_[a].x < points_[b].x;
        });
        nodes_[k].left = build(ids, l, m, depth + 1);
        nodes_[k].right = build(ids, m, r, depth + 1);
        if (nodes_[k].left != -1) parent_[nodes_[k].left] = k;
        if (nodes_[k].right != -1) parent_[nodes_[k].right] = k;
        pull(k);
        return k;
    }

    bool disjoint(int k, long long l, long long d, long long r, long long u) const {
        const auto& nd = nodes_[k];
        return nd.max_x < l || r <= nd.min_x || nd.max_y < d || u <= nd.min_y;
    }

    bool covered(int k, long long l, long long d, long long r, long long u) const {
        const auto& nd = nodes_[k];
        return l <= nd.min_x && nd.max_x < r && d <= nd.min_y && nd.max_y < u;
    }

    void all_apply(int k, affine f) {
        if (k == -1 || nodes_[k].active_count == 0) return;
        nodes_[k].sum = f.a * nodes_[k].sum + f.b * T(nodes_[k].active_count);
        nodes_[k].lazy = compose(f, nodes_[k].lazy);
    }

    void push(int k) {
        affine f = nodes_[k].lazy;
        if (f.a == T(1) && f.b == T(0)) return;
        all_apply(nodes_[k].left, f);
        all_apply(nodes_[k].right, f);
        nodes_[k].lazy = {T(1), T(0)};
    }

    void pull(int k) {
        auto& nd = nodes_[k];
        nd.active_count = 0;
        nd.sum = T{};
        if (nd.point_id != -1) {
            if (points_[nd.point_id].active) {
                nd.active_count = 1;
                nd.sum = points_[nd.point_id].w;
            }
            return;
        }
        if (nd.left != -1) {
            nd.active_count += nodes_[nd.left].active_count;
            nd.sum += nodes_[nd.left].sum;
        }
        if (nd.right != -1) {
            nd.active_count += nodes_[nd.right].active_count;
            nd.sum += nodes_[nd.right].sum;
        }
    }

    void set_weight(int id, T w) {
        int k = leaf_[id];
        std::vector<int> path;
        for (int v = k; v != -1; v = parent_[v]) path.push_back(v);
        for (int i = static_cast<int>(path.size()) - 1; i >= 0; --i) push(path[i]);
        points_[id].w = w;
        nodes_[k].active_count = 1;
        nodes_[k].sum = w;
        for (int i = 1; i < static_cast<int>(path.size()); ++i) pull(path[i]);
    }

    T sum(int k, long long l, long long d, long long r, long long u) {
        if (k == -1 || disjoint(k, l, d, r, u) || nodes_[k].active_count == 0) return T{};
        if (covered(k, l, d, r, u)) return nodes_[k].sum;
        push(k);
        if (nodes_[k].point_id != -1) {
            const auto& p = points_[nodes_[k].point_id];
            return p.active && l <= p.x && p.x < r && d <= p.y && p.y < u ? nodes_[k].sum : T{};
        }
        return sum(nodes_[k].left, l, d, r, u) + sum(nodes_[k].right, l, d, r, u);
    }

    void apply(int k, long long l, long long d, long long r, long long u, affine f) {
        if (k == -1 || disjoint(k, l, d, r, u) || nodes_[k].active_count == 0) return;
        if (covered(k, l, d, r, u)) {
            all_apply(k, f);
            return;
        }
        push(k);
        if (nodes_[k].point_id != -1) {
            const auto& p = points_[nodes_[k].point_id];
            if (p.active && l <= p.x && p.x < r && d <= p.y && p.y < u) all_apply(k, f);
            return;
        }
        apply(nodes_[k].left, l, d, r, u, f);
        apply(nodes_[k].right, l, d, r, u, f);
        pull(k);
    }

    std::vector<point> points_;
    mode mode_ = mode::kd;
    std::vector<long long> group_keys_;
    std::vector<group> groups_;
    std::vector<int> group_id_;
    std::vector<int> point_pos_;
    std::vector<node> nodes_;
    std::vector<int> parent_;
    std::vector<int> leaf_;
    int root_ = -1;
};

}  // namespace poe
