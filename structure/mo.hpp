#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace poe {

class mo {
public:
    enum class order_type {
        hilbert,
        block,
    };

    struct query {
        int l;
        int r;
        int id;
    };

    explicit mo(int n, order_type order = order_type::hilbert) : n_(n), order_(order) {
        assert(n >= 0);
        block_size_ = std::max(1, static_cast<int>(std::sqrt(std::max(1, n_))));
    }

    int add_query(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        int id = static_cast<int>(queries_.size());
        queries_.push_back({l, r, id});
        return id;
    }

    int size() const { return static_cast<int>(queries_.size()); }
    const std::vector<query>& queries() const { return queries_; }

    std::vector<query> ordered_queries() const {
        std::vector<query> res = queries_;
        if (order_ == order_type::hilbert) {
            int pow = 0;
            while ((std::uint64_t(1) << pow) <= static_cast<std::uint64_t>(std::max(1, n_))) ++pow;
            std::sort(res.begin(), res.end(), [&](const query& a, const query& b) {
                return hilbert_order(a.l, a.r, pow, 0) < hilbert_order(b.l, b.r, pow, 0);
            });
        } else {
            std::sort(res.begin(), res.end(), [&](const query& a, const query& b) {
                int ab = a.l / block_size_;
                int bb = b.l / block_size_;
                if (ab != bb) return ab < bb;
                return (ab & 1) ? a.r > b.r : a.r < b.r;
            });
        }
        return res;
    }

    template <class AddLeft, class AddRight, class EraseLeft, class EraseRight, class Answer>
    void run(AddLeft add_left, AddRight add_right, EraseLeft erase_left, EraseRight erase_right, Answer answer) const {
        int l = 0, r = 0;
        for (auto q : ordered_queries()) {
            while (l > q.l) add_left(--l);
            while (r < q.r) add_right(r++);
            while (l < q.l) erase_left(l++);
            while (r > q.r) erase_right(--r);
            call_answer(answer, q);
        }
    }

    template <class Add, class Erase, class Answer>
    void run(Add add, Erase erase, Answer answer) const {
        run(add, add, erase, erase, answer);
    }

private:
    static std::uint64_t hilbert_order(int x, int y, int pow, int rot) {
        if (pow == 0) return 0;
        int hpow = 1 << (pow - 1);
        int seg = 0;
        if (x < hpow) {
            seg = (y < hpow) ? 0 : 3;
        } else {
            seg = (y < hpow) ? 1 : 2;
        }
        seg = (seg + rot) & 3;
        static constexpr int rotate_delta[4] = {3, 0, 0, 1};
        int nx = x & (hpow - 1);
        int ny = y & (hpow - 1);
        int nrot = (rot + rotate_delta[seg]) & 3;
        std::uint64_t sub_square_size = std::uint64_t(1) << (2 * pow - 2);
        std::uint64_t res = std::uint64_t(seg) * sub_square_size;
        std::uint64_t add = hilbert_order(nx, ny, pow - 1, nrot);
        if (seg == 1 || seg == 2) res += add;
        else res += sub_square_size - add - 1;
        return res;
    }

    template <class Answer>
    static void call_answer(Answer& answer, const query& q) {
        if constexpr (std::is_invocable_v<Answer, int, int, int>) {
            answer(q.id, q.l, q.r);
        } else {
            answer(q.id);
        }
    }

    int n_ = 0;
    int block_size_ = 1;
    order_type order_ = order_type::hilbert;
    std::vector<query> queries_;
};

}  // namespace poe
