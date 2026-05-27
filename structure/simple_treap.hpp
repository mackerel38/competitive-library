#pragma once

#include "utility/randgen.hpp"

#include <cassert>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace poe {

template <class T>
class simple_treap {
public:
    struct node {
        T value;
        std::uint64_t priority;
        int size;
        node* left;
        node* right;

        node(const T& value, std::uint64_t priority)
            : value(value), priority(priority), size(1), left(nullptr), right(nullptr) {}
    };

    using node_ptr = node*;

    simple_treap() = default;
    explicit simple_treap(const std::vector<T>& v) { root_ = build(v); }

    node_ptr root() const { return root_; }
    int size() const { return size(root_); }
    bool empty() const { return root_ == nullptr; }

    node_ptr make_node(const T& value) {
        nodes_->push_back(std::make_unique<node>(value, global_random_engine()()));
        return nodes_->back().get();
    }

    static int size(node_ptr t) { return t ? t->size : 0; }

    static node_ptr merge(node_ptr l, node_ptr r) {
        if (!l) return r;
        if (!r) return l;
        if (l->priority < r->priority) {
            l->right = merge(l->right, r);
            return update(l);
        }
        r->left = merge(l, r->left);
        return update(r);
    }

    static std::pair<node_ptr, node_ptr> split(node_ptr t, int k) {
        assert(0 <= k && k <= size(t));
        if (!t) return {nullptr, nullptr};
        if (k <= size(t->left)) {
            auto [l, r] = split(t->left, k);
            t->left = r;
            return {l, update(t)};
        }
        auto [l, r] = split(t->right, k - size(t->left) - 1);
        t->right = l;
        return {update(t), r};
    }

    node_ptr build(const std::vector<T>& v) {
        node_ptr t = nullptr;
        for (const T& x : v) t = merge(t, make_node(x));
        return t;
    }

    void set_root(node_ptr t) { root_ = t; }

    void merge_back(simple_treap& other) {
        root_ = merge(root_, other.root_);
        other.root_ = nullptr;
    }

    simple_treap split_off(int k) {
        auto [l, r] = split(root_, k);
        root_ = l;
        simple_treap res;
        res.root_ = r;
        res.nodes_ = nodes_;
        return res;
    }

    void insert(int p, const T& value) {
        assert(0 <= p && p <= size());
        auto [l, r] = split(root_, p);
        root_ = merge(merge(l, make_node(value)), r);
    }

    T erase(int p) {
        assert(0 <= p && p < size());
        auto [l, mr] = split(root_, p);
        auto [m, r] = split(mr, 1);
        T res = m->value;
        root_ = merge(l, r);
        return res;
    }

    T get(int p) const {
        assert(0 <= p && p < size());
        node_ptr t = root_;
        while (t) {
            int ls = size(t->left);
            if (p < ls) {
                t = t->left;
            } else if (p == ls) {
                return t->value;
            } else {
                p -= ls + 1;
                t = t->right;
            }
        }
        assert(false);
        return T{};
    }

    void set(int p, const T& value) {
        assert(0 <= p && p < size());
        node_ptr t = root_;
        while (t) {
            int ls = size(t->left);
            if (p < ls) {
                t = t->left;
            } else if (p == ls) {
                t->value = value;
                return;
            } else {
                p -= ls + 1;
                t = t->right;
            }
        }
    }

    std::vector<T> to_vector() const {
        std::vector<T> res;
        res.reserve(size());
        dump(root_, res);
        return res;
    }

private:
    static node_ptr update(node_ptr t) {
        if (t) t->size = 1 + size(t->left) + size(t->right);
        return t;
    }

    static void dump(node_ptr t, std::vector<T>& res) {
        if (!t) return;
        dump(t->left, res);
        res.push_back(t->value);
        dump(t->right, res);
    }

    node_ptr root_ = nullptr;
    std::shared_ptr<std::vector<std::unique_ptr<node>>> nodes_ =
        std::make_shared<std::vector<std::unique_ptr<node>>>();
};

}  // namespace poe
