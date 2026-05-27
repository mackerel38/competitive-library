#pragma once

#include "utility/randgen.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

namespace poe {

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
class treap {
public:
    struct node {
        S value;
        S prod;
        S reverse_prod;
        F lazy;
        std::uint64_t priority;
        int size;
        bool rev;
        node* left;
        node* right;

        node(const S& value, std::uint64_t priority)
            : value(value),
              prod(value),
              reverse_prod(value),
              lazy(id()),
              priority(priority),
              size(1),
              rev(false),
              left(nullptr),
              right(nullptr) {}
    };

    using node_ptr = node*;

    treap() = default;
    explicit treap(const std::vector<S>& v) { root_ = build(v); }

    node_ptr root() const { return root_; }
    int size() const { return size(root_); }
    bool empty() const { return root_ == nullptr; }

    node_ptr make_node(const S& value) {
        nodes_->push_back(std::make_unique<node>(value, global_random_engine()()));
        return nodes_->back().get();
    }

    static int size(node_ptr t) { return t ? t->size : 0; }
    static S prod(node_ptr t) { return t ? t->prod : e(); }

    static node_ptr merge(node_ptr l, node_ptr r) {
        if (!l) return r;
        if (!r) return l;
        if (l->priority < r->priority) {
            push(l);
            l->right = merge(l->right, r);
            return update(l);
        }
        push(r);
        r->left = merge(l, r->left);
        return update(r);
    }

    static std::pair<node_ptr, node_ptr> split(node_ptr t, int k) {
        assert(0 <= k && k <= size(t));
        if (!t) return {nullptr, nullptr};
        push(t);
        if (k <= size(t->left)) {
            auto [l, r] = split(t->left, k);
            t->left = r;
            return {l, update(t)};
        }
        auto [l, r] = split(t->right, k - size(t->left) - 1);
        t->right = l;
        return {update(t), r};
    }

    node_ptr build(const std::vector<S>& v) {
        node_ptr t = nullptr;
        for (const S& x : v) t = merge(t, make_node(x));
        return t;
    }

    void set_root(node_ptr t) { root_ = t; }

    void merge_back(treap& other) {
        root_ = merge(root_, other.root_);
        other.root_ = nullptr;
    }

    treap split_off(int k) {
        auto [l, r] = split(root_, k);
        root_ = l;
        treap res;
        res.root_ = r;
        res.nodes_ = nodes_;
        return res;
    }

    void insert(int p, const S& x) {
        assert(0 <= p && p <= size());
        auto [l, r] = split(root_, p);
        root_ = merge(merge(l, make_node(x)), r);
    }

    S erase(int p) {
        assert(0 <= p && p < size());
        auto [l, mr] = split(root_, p);
        auto [m, r] = split(mr, 1);
        S res = m->value;
        root_ = merge(l, r);
        return res;
    }

    S get(int p) {
        assert(0 <= p && p < size());
        auto [l, mr] = split(root_, p);
        auto [m, r] = split(mr, 1);
        S res = m->value;
        root_ = merge(merge(l, m), r);
        return res;
    }

    S kth(int k) { return get(k); }

    void set(int p, const S& x) {
        assert(0 <= p && p < size());
        auto [l, mr] = split(root_, p);
        auto [m, r] = split(mr, 1);
        m->value = x;
        m->prod = x;
        m->reverse_prod = x;
        m->lazy = id();
        root_ = merge(merge(l, update(m)), r);
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        auto [a, bc] = split(root_, l);
        auto [b, c] = split(bc, r - l);
        S res = prod(b);
        root_ = merge(merge(a, b), c);
        return res;
    }

    S all_prod() const { return prod(root_); }

    template <bool (*g)(S)>
    int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }

    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= size());
        assert(g(e()));
        auto [a, b] = split(root_, l);
        S sm = e();
        int res = max_right_from(b, sm, g);
        root_ = merge(a, b);
        return l + res;
    }

    template <bool (*g)(S)>
    int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }

    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= size());
        assert(g(e()));
        auto [a, b] = split(root_, r);
        S sm = e();
        int res = min_left_from(a, sm, g);
        root_ = merge(a, b);
        return res;
    }

    void apply(int p, const F& f) {
        assert(0 <= p && p < size());
        apply(p, p + 1, f);
    }

    void apply(int l, int r, const F& f) {
        assert(0 <= l && l <= r && r <= size());
        auto [a, bc] = split(root_, l);
        auto [b, c] = split(bc, r - l);
        all_apply(b, f);
        root_ = merge(merge(a, b), c);
    }

    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        auto [a, bc] = split(root_, l);
        auto [b, c] = split(bc, r - l);
        all_reverse(b);
        root_ = merge(merge(a, b), c);
    }

    void rotate_left(int l, int m, int r) {
        rotate(l, m, r);
    }

    void rotate(int l, int m, int r) {
        assert(0 <= l && l <= m && m <= r && r <= size());
        auto [a, bcd] = split(root_, l);
        auto [b, cd] = split(bcd, m - l);
        auto [c, d] = split(cd, r - m);
        root_ = merge(merge(merge(a, c), b), d);
    }

    void rotate_right(int l, int m, int r) {
        rotate(l, m, r);
    }

    std::vector<S> to_vector() {
        std::vector<S> res;
        res.reserve(size());
        dump(root_, res);
        return res;
    }

private:
    static node_ptr update(node_ptr t) {
        if (!t) return t;
        t->size = 1 + size(t->left) + size(t->right);
        t->prod = op(op(prod(t->left), t->value), prod(t->right));
        t->reverse_prod = op(op(reverse_prod(t->right), t->value), reverse_prod(t->left));
        return t;
    }

    static S reverse_prod(node_ptr t) { return t ? t->reverse_prod : e(); }

    static void all_apply(node_ptr t, const F& f) {
        if (!t) return;
        t->value = mapping(f, t->value);
        t->prod = mapping(f, t->prod);
        t->reverse_prod = mapping(f, t->reverse_prod);
        t->lazy = composition(f, t->lazy);
    }

    static void all_reverse(node_ptr t) {
        if (!t) return;
        std::swap(t->left, t->right);
        std::swap(t->prod, t->reverse_prod);
        t->rev = !t->rev;
    }

    static void push(node_ptr t) {
        if (!t) return;
        if (t->rev) {
            all_reverse(t->left);
            all_reverse(t->right);
            t->rev = false;
        }
        all_apply(t->left, t->lazy);
        all_apply(t->right, t->lazy);
        t->lazy = id();
    }

    static void dump(node_ptr t, std::vector<S>& res) {
        if (!t) return;
        push(t);
        dump(t->left, res);
        res.push_back(t->value);
        dump(t->right, res);
        update(t);
    }

    template <class G>
    static int max_right_from(node_ptr t, S& sm, G& g) {
        if (!t) return 0;
        push(t);
        S with_left = op(sm, prod(t->left));
        if (!g(with_left)) return max_right_from(t->left, sm, g);
        S with_node = op(with_left, t->value);
        if (!g(with_node)) return size(t->left);
        sm = with_node;
        return size(t->left) + 1 + max_right_from(t->right, sm, g);
    }

    template <class G>
    static int min_left_from(node_ptr t, S& sm, G& g) {
        if (!t) return 0;
        push(t);
        S with_right = op(prod(t->right), sm);
        if (!g(with_right)) return size(t->left) + 1 + min_left_from(t->right, sm, g);
        S with_node = op(t->value, with_right);
        if (!g(with_node)) return size(t->left) + 1;
        sm = with_node;
        return min_left_from(t->left, sm, g);
    }

    node_ptr root_ = nullptr;
    std::shared_ptr<std::vector<std::unique_ptr<node>>> nodes_ =
        std::make_shared<std::vector<std::unique_ptr<node>>>();
};

}  // namespace poe
