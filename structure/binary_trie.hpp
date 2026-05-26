#pragma once

#include <cassert>
#include <limits>
#include <memory>

namespace poe {

template <class UInt = unsigned long long, int B = std::numeric_limits<UInt>::digits>
class binary_trie {
    static_assert(std::numeric_limits<UInt>::is_integer);
    static_assert(!std::numeric_limits<UInt>::is_signed);

public:
    using value_type = UInt;

    binary_trie() : root_(std::make_unique<node>()) {}

    int size() const { return root_->count; }
    bool empty() const { return size() == 0; }

    void insert(UInt x, int k = 1) {
        assert(k >= 0);
        add(root_.get(), x, k, B - 1);
    }

    void erase(UInt x, int k = 1) {
        assert(0 <= k && k <= count(x));
        add(root_.get(), x, -k, B - 1);
    }

    int count(UInt x) const {
        const node* v = root_.get();
        for (int b = B - 1; b >= 0; --b) {
            int d = static_cast<int>((x >> b) & 1);
            v = v->child[d].get();
            if (v == nullptr) return 0;
        }
        return v->count;
    }

    bool contains(UInt x) const { return count(x) > 0; }

    UInt kth(int k, UInt xor_value = 0) const {
        assert(0 <= k && k < size());
        const node* v = root_.get();
        UInt res = 0;
        for (int b = B - 1; b >= 0; --b) {
            int xd = static_cast<int>((xor_value >> b) & 1);
            int left_count = count_child(v, xd);
            if (k < left_count) {
                v = v->child[xd].get();
            } else {
                k -= left_count;
                res |= UInt(1) << b;
                v = v->child[xd ^ 1].get();
            }
        }
        return res ^ xor_value;
    }

    UInt min_element(UInt xor_value = 0) const {
        assert(!empty());
        return kth(0, xor_value);
    }

    UInt max_element(UInt xor_value = 0) const {
        assert(!empty());
        return kth(size() - 1, xor_value);
    }

    int count_less(UInt x, UInt xor_value = 0) const {
        const node* v = root_.get();
        int res = 0;
        for (int b = B - 1; b >= 0 && v != nullptr; --b) {
            int xd = static_cast<int>((xor_value >> b) & 1);
            if ((x >> b) & 1) {
                res += count_child(v, xd);
                v = v->child[xd ^ 1].get();
            } else {
                v = v->child[xd].get();
            }
        }
        return res;
    }

    int count_range(UInt l, UInt r, UInt xor_value = 0) const {
        assert(l <= r);
        return count_less(r, xor_value) - count_less(l, xor_value);
    }

    UInt lower_bound(UInt x, UInt xor_value = 0) const {
        int k = count_less(x, xor_value);
        assert(k < size());
        return kth(k, xor_value);
    }

private:
    struct node {
        int count = 0;
        std::unique_ptr<node> child[2];
    };

    static int count_child(const node* v, int d) { return v->child[d] ? v->child[d]->count : 0; }

    static void add(node* v, UInt x, int k, int bit) {
        v->count += k;
        if (bit < 0) return;
        int d = static_cast<int>((x >> bit) & 1);
        if (!v->child[d]) v->child[d] = std::make_unique<node>();
        add(v->child[d].get(), x, k, bit - 1);
    }

    std::unique_ptr<node> root_;
};

}  // namespace poe
