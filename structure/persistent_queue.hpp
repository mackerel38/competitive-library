#pragma once

#include <cassert>
#include <memory>
#include <vector>

namespace poe {

template <class T>
class persistent_queue {
public:
    struct node {
        T value;
        std::shared_ptr<node> parent;
        int depth;
        std::vector<std::shared_ptr<node>> up;

        node(const T& value, std::shared_ptr<node> parent) : value(value), parent(parent), depth(parent ? parent->depth + 1 : 0) {
            up.push_back(parent);
            for (int k = 1; up[k - 1]; ++k) up.push_back(up[k - 1]->up.size() >= static_cast<std::size_t>(k) ? up[k - 1]->up[k - 1] : nullptr);
        }
    };

    persistent_queue() = default;

    int size() const { return back_ ? back_->depth - pop_count_ + 1 : 0; }
    bool empty() const { return size() == 0; }

    persistent_queue push(const T& x) const {
        persistent_queue res = *this;
        res.back_ = std::make_shared<node>(x, back_);
        return res;
    }

    persistent_queue pop() const {
        assert(!empty());
        persistent_queue res = *this;
        ++res.pop_count_;
        if (res.pop_count_ > res.back_->depth) {
            res.back_.reset();
            res.pop_count_ = 0;
        }
        return res;
    }

    T front() const {
        assert(!empty());
        return ancestor(back_, size() - 1)->value;
    }

    T back() const {
        assert(!empty());
        return back_->value;
    }

private:
    static std::shared_ptr<node> ancestor(std::shared_ptr<node> v, int steps) {
        for (int k = 0; steps; ++k) {
            if (steps & 1) v = v->up[k];
            steps >>= 1;
        }
        return v;
    }

    std::shared_ptr<node> back_;
    int pop_count_ = 0;
};

}  // namespace poe
