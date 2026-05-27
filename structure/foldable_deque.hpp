#pragma once

#include <cassert>
#include <vector>

namespace poe {

template <class S, S (*op)(S, S), S (*e)()>
class foldable_deque {
public:
    foldable_deque() {
        front_prod_.push_back(e());
        back_prod_.push_back(e());
    }

    int size() const { return static_cast<int>(front_.size() + back_.size()); }
    bool empty() const { return size() == 0; }

    void push_front(const S& x) {
        front_.push_back(x);
        front_prod_.push_back(op(x, front_prod_.back()));
    }

    void push_back(const S& x) {
        back_.push_back(x);
        back_prod_.push_back(op(back_prod_.back(), x));
    }

    void pop_front() {
        assert(!empty());
        if (front_.empty()) rebuild_from_back();
        front_.pop_back();
        front_prod_.pop_back();
    }

    void pop_back() {
        assert(!empty());
        if (back_.empty()) rebuild_from_front();
        back_.pop_back();
        back_prod_.pop_back();
    }

    S fold() const { return op(front_prod_.back(), back_prod_.back()); }

private:
    void rebuild_front_prod() {
        front_prod_.assign(1, e());
        for (const S& x : front_) front_prod_.push_back(op(x, front_prod_.back()));
    }

    void rebuild_back_prod() {
        back_prod_.assign(1, e());
        for (const S& x : back_) back_prod_.push_back(op(back_prod_.back(), x));
    }

    void rebuild_from_back() {
        int keep = static_cast<int>(back_.size()) / 2;
        int move = static_cast<int>(back_.size()) - keep;
        front_.clear();
        front_.reserve(move);
        for (int i = move - 1; i >= 0; --i) front_.push_back(back_[i]);
        std::vector<S> next_back;
        next_back.reserve(keep);
        for (int i = move; i < static_cast<int>(back_.size()); ++i) next_back.push_back(back_[i]);
        back_.swap(next_back);
        rebuild_front_prod();
        rebuild_back_prod();
    }

    void rebuild_from_front() {
        int keep = static_cast<int>(front_.size()) / 2;
        int move = static_cast<int>(front_.size()) - keep;
        back_.clear();
        back_.reserve(move);
        for (int i = move - 1; i >= 0; --i) back_.push_back(front_[i]);
        std::vector<S> next_front;
        next_front.reserve(keep);
        for (int i = move; i < static_cast<int>(front_.size()); ++i) next_front.push_back(front_[i]);
        front_.swap(next_front);
        rebuild_front_prod();
        rebuild_back_prod();
    }

    std::vector<S> front_;
    std::vector<S> back_;
    std::vector<S> front_prod_;
    std::vector<S> back_prod_;
};

}  // namespace poe
