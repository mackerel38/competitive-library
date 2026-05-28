#pragma once

#include "structure/segtree.hpp"

#include <cassert>
#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace poe {

template <class Mint>
class range_sort_range_composite {
public:
    struct item {
        int p;
        Mint a;
        Mint b;
    };
    struct affine {
        Mint a;
        Mint b;
    };

    static affine op(affine f, affine g) {
        return {f.a * g.a, g.a * f.b + g.b};
    }
    static affine e() { return {Mint(1), Mint(0)}; }

    range_sort_range_composite() = default;
    explicit range_sort_range_composite(const std::vector<item>& v) : n_(static_cast<int>(v.size())), seg_(std::vector<affine>(n_, e())) {
        for (int i = 0; i < n_; ++i) {
            node_ptr root = set_node(nullptr, 0, max_p_, v[i]);
            blocks_[i] = {root, false};
            seg_.set(i, block_prod(blocks_[i]));
        }
    }

    int size() const { return n_; }

    void set(int i, item x) {
        assert(0 <= i && i < n_);
        split(i);
        split(i + 1);
        auto it = blocks_.find(i);
        seg_.set(i, e());
        blocks_.erase(it);
        node_ptr root = set_node(nullptr, 0, max_p_, x);
        blocks_[i] = {root, false};
        seg_.set(i, block_prod(blocks_[i]));
    }

    affine prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        split(l);
        split(r);
        return seg_.prod(l, r);
    }

    Mint apply(int l, int r, Mint x) {
        affine f = prod(l, r);
        return f.a * x + f.b;
    }

    void sort_ascending(int l, int r) { sort_range(l, r, false); }
    void sort_descending(int l, int r) { sort_range(l, r, true); }

private:
    struct node;
    using node_ptr = node*;
    struct node {
        node_ptr left = nullptr;
        node_ptr right = nullptr;
        int size = 0;
        affine lr = e();
        affine rl = e();
    };
    struct block {
        node_ptr root = nullptr;
        bool rev = false;
    };

    static int size(node_ptr t) { return t ? t->size : 0; }
    static affine prod_lr(node_ptr t) { return t ? t->lr : e(); }
    static affine prod_rl(node_ptr t) { return t ? t->rl : e(); }

    node_ptr new_node() {
        nodes_.push_back(std::make_unique<node>());
        return nodes_.back().get();
    }

    static void pull(node_ptr t) {
        if (!t) return;
        t->size = size(t->left) + size(t->right);
        t->lr = op(prod_lr(t->left), prod_lr(t->right));
        t->rl = op(prod_rl(t->right), prod_rl(t->left));
    }

    node_ptr set_node(node_ptr t, int nl, int nr, item x) {
        if (!t) t = new_node();
        if (nr - nl == 1) {
            t->size = 1;
            t->lr = t->rl = {x.a, x.b};
            return t;
        }
        int mid = (nl + nr) >> 1;
        if (x.p < mid) t->left = set_node(t->left, nl, mid, x);
        else t->right = set_node(t->right, mid, nr, x);
        pull(t);
        return t;
    }

    node_ptr merge(node_ptr a, node_ptr b) {
        if (!a) return b;
        if (!b) return a;
        a->left = merge(a->left, b->left);
        a->right = merge(a->right, b->right);
        pull(a);
        return a;
    }

    std::pair<node_ptr, node_ptr> split_by_k(node_ptr t, int k, bool rev) {
        assert(0 <= k && k <= size(t));
        if (!t || k == 0) return {nullptr, t};
        if (k == size(t)) return {t, nullptr};
        node_ptr a = new_node();
        node_ptr b = new_node();
        if (!rev) {
            int left_size = size(t->left);
            if (k < left_size) {
                auto [ll, lr] = split_by_k(t->left, k, rev);
                a->left = ll;
                b->left = lr;
                b->right = t->right;
            } else if (k == left_size) {
                a->left = t->left;
                b->right = t->right;
            } else {
                auto [rl, rr] = split_by_k(t->right, k - left_size, rev);
                a->left = t->left;
                a->right = rl;
                b->right = rr;
            }
        } else {
            int right_size = size(t->right);
            if (k < right_size) {
                auto [rr, rl] = split_by_k(t->right, k, rev);
                a->right = rr;
                b->right = rl;
                b->left = t->left;
            } else if (k == right_size) {
                a->right = t->right;
                b->left = t->left;
            } else {
                auto [lr, ll] = split_by_k(t->left, k - right_size, rev);
                a->right = t->right;
                a->left = lr;
                b->left = ll;
            }
        }
        pull(a);
        pull(b);
        return {a, b};
    }

    affine block_prod(const block& b) const {
        return b.rev ? prod_rl(b.root) : prod_lr(b.root);
    }

    void set_block(int l, block b) {
        blocks_[l] = b;
        seg_.set(l, block_prod(b));
    }

    void split(int x) {
        assert(0 <= x && x <= n_);
        if (x == n_ || blocks_.count(x)) return;
        auto it = std::prev(blocks_.upper_bound(x));
        int l = it->first;
        block b = it->second;
        int left_len = x - l;
        auto [left_root, right_root] = split_by_k(b.root, left_len, b.rev);
        it->second.root = left_root;
        seg_.set(l, block_prod(it->second));
        set_block(x, {right_root, b.rev});
    }

    void sort_range(int l, int r, bool rev) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) return;
        split(l);
        split(r);
        auto it = blocks_.lower_bound(l);
        node_ptr root = nullptr;
        std::vector<int> erase_keys;
        while (it != blocks_.end() && it->first < r) {
            root = merge(root, it->second.root);
            seg_.set(it->first, e());
            erase_keys.push_back(it->first);
            ++it;
        }
        for (int key : erase_keys) blocks_.erase(key);
        set_block(l, {root, rev});
    }

    static constexpr int max_p_ = 1 << 30;
    int n_ = 0;
    segtree<affine, op, e> seg_;
    std::map<int, block> blocks_;
    std::vector<std::unique_ptr<node>> nodes_;
};

}  // namespace poe
