#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class S, S (*op)(S, S), S (*e)()>
class swag {
public:
    swag() = default;

    int size() const { return static_cast<int>(front_.size() + back_.size()); }
    bool empty() const { return size() == 0; }

    void push(const S& x) {
        S prod = back_.empty() ? x : op(back_.back().second, x);
        back_.push_back({x, prod});
    }

    void pop() {
        assert(!empty());
        if (front_.empty()) move_back_to_front();
        front_.pop_back();
    }

    S fold() const {
        S l = front_.empty() ? e() : front_.back().second;
        S r = back_.empty() ? e() : back_.back().second;
        return op(l, r);
    }

    S front() {
        assert(!empty());
        if (front_.empty()) move_back_to_front();
        return front_.back().first;
    }

    S back() const {
        assert(!empty());
        return back_.empty() ? front_.front().first : back_.back().first;
    }

    void clear() {
        front_.clear();
        back_.clear();
    }

private:
    void move_back_to_front() {
        while (!back_.empty()) {
            S x = back_.back().first;
            back_.pop_back();
            S prod = front_.empty() ? x : op(x, front_.back().second);
            front_.push_back({x, prod});
        }
    }

    std::vector<std::pair<S, S>> front_;
    std::vector<std::pair<S, S>> back_;
};

}  // namespace poe
