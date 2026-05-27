#pragma once

#include "utility/randgen.hpp"

#include <cassert>
#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace poe {

template <class T, class Compare = std::less<T>>
class ordered_set {
public:
    ordered_set() : nodes_(std::make_shared<std::vector<std::unique_ptr<node>>>()) {}

    int size() const { return size(root_); }
    bool empty() const { return root_ == nullptr; }

    bool contains(const T& x) const {
        node* t = root_;
        while (t) {
            if (comp_(x, t->key)) {
                t = t->left;
            } else if (comp_(t->key, x)) {
                t = t->right;
            } else {
                return true;
            }
        }
        return false;
    }

    bool insert(const T& x) {
        if (contains(x)) return false;
        auto [l, r] = split(root_, x);
        root_ = merge(merge(l, make_node(x)), r);
        return true;
    }

    bool erase(const T& x) {
        if (!contains(x)) return false;
        auto [l, ge] = split(root_, x);
        auto [eq, r] = split_le(ge, x);
        root_ = merge(l, r);
        return eq != nullptr;
    }

    int order_of_key(const T& x) const {
        int res = 0;
        node* t = root_;
        while (t) {
            if (comp_(t->key, x)) {
                res += size(t->left) + 1;
                t = t->right;
            } else {
                t = t->left;
            }
        }
        return res;
    }

    T kth(int k) const {
        assert(0 <= k && k < size());
        node* t = root_;
        while (t) {
            int ls = size(t->left);
            if (k < ls) {
                t = t->left;
            } else if (k == ls) {
                return t->key;
            } else {
                k -= ls + 1;
                t = t->right;
            }
        }
        assert(false);
        return T{};
    }

    T min() const {
        assert(!empty());
        return kth(0);
    }

    T max() const {
        assert(!empty());
        return kth(size() - 1);
    }

    T lower_bound(const T& x) const {
        int k = order_of_key(x);
        assert(k < size());
        return kth(k);
    }

    T upper_bound(const T& x) const {
        int k = order_of_key_upper(x);
        assert(k < size());
        return kth(k);
    }

    int count_lt(const T& x) const { return order_of_key(x); }
    int count_le(const T& x) const { return order_of_key_upper(x); }
    int count_ge(const T& x) const { return size() - count_lt(x); }
    int count_gt(const T& x) const { return size() - count_le(x); }

private:
    struct node {
        T key;
        std::uint64_t priority;
        int size;
        node* left;
        node* right;
        node(const T& key, std::uint64_t priority)
            : key(key), priority(priority), size(1), left(nullptr), right(nullptr) {}
    };

    static int size(node* t) { return t ? t->size : 0; }
    static node* update(node* t) {
        if (t) t->size = 1 + size(t->left) + size(t->right);
        return t;
    }

    node* make_node(const T& x) {
        nodes_->push_back(std::make_unique<node>(x, global_random_engine()()));
        return nodes_->back().get();
    }

    node* merge(node* l, node* r) const {
        if (!l) return r;
        if (!r) return l;
        if (l->priority < r->priority) {
            l->right = merge(l->right, r);
            return update(l);
        }
        r->left = merge(l, r->left);
        return update(r);
    }

    std::pair<node*, node*> split(node* t, const T& x) const {
        if (!t) return {nullptr, nullptr};
        if (comp_(t->key, x)) {
            auto [l, r] = split(t->right, x);
            t->right = l;
            return {update(t), r};
        }
        auto [l, r] = split(t->left, x);
        t->left = r;
        return {l, update(t)};
    }

    std::pair<node*, node*> split_le(node* t, const T& x) const {
        if (!t) return {nullptr, nullptr};
        if (!comp_(x, t->key)) {
            auto [l, r] = split_le(t->right, x);
            t->right = l;
            return {update(t), r};
        }
        auto [l, r] = split_le(t->left, x);
        t->left = r;
        return {l, update(t)};
    }

    int order_of_key_upper(const T& x) const {
        int res = 0;
        node* t = root_;
        while (t) {
            if (!comp_(x, t->key)) {
                res += size(t->left) + 1;
                t = t->right;
            } else {
                t = t->left;
            }
        }
        return res;
    }

    node* root_ = nullptr;
    Compare comp_{};
    std::shared_ptr<std::vector<std::unique_ptr<node>>> nodes_;
};

}  // namespace poe
