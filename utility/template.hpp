#pragma once
#ifdef poe
#define debug(...) do { cerr << #__VA_ARGS__ << ": "; debug_out(__VA_ARGS__); } while (false)
#else
#define debug(...) ((void)0)
#endif

#include <bits/stdc++.h>
using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
using ld = long double;
using str = string;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vvvi = vector<vector<vector<int>>>;
using pi = pair<int, int>;
using ppi = pair<int, pair<int, int>>;
using pppi = pair<int, pair<int, pair<int, int>>>;
using vpi = vector<pair<int, int>>;
using vvpi = vector<vector<pair<int, int>>>;
using vvvpi = vector<vector<vector<pair<int, int>>>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;
using vvvll = vector<vector<vector<long long>>>;
using pll = pair<long long, long long>;
using ppll = pair<long long, pair<long long, long long>>;
using pppll = pair<long long, pair<long long, pair<long long, long long>>>;
using vpll = vector<pair<long long, long long>>;
using vvpll = vector<vector<pair<long long, long long>>>;
using vvvpll = vector<vector<vector<pair<long long, long long>>>>;
template <class T> using pairs = pair<T, T>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vec<vec<T>>;
template <class T> using vvvec = vec<vec<vec<T>>>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

#define vv(type, name, x, y, ...) vector<vector<type>> name((x), vector<type>((y), ##__VA_ARGS__))
#define vvv(type, name, x, y, z, ...) vector<vector<vector<type>>> name((x), vector<vector<type>>((y), vector<type>((z), ##__VA_ARGS__)))

#define rep_1(n) for (long long _=0LL; _<(long long)(n); ++_)
#define rep_2(i, n) for (long long i=0LL; i<(long long)(n); ++i)
#define rep_3(i, l, r) for (long long i=(long long)(l); i<(long long)(r); ++i)
#define rep_4(i, l, r, s) for (long long i=(long long)(l); i<(long long)(r); i+=(long long)(s))
#define overload_rep(a, b, c, d, e, ...) e
#define rep(...) overload_rep(__VA_ARGS__, rep_4, rep_3, rep_2, rep_1)(__VA_ARGS__)

#define rep1_1(n) for (long long _=1LL; _<=(long long)(n); ++_)
#define rep1_2(i, n) for (long long i=1LL; i<=(long long)(n); ++i)
#define rep1_3(i, l, r) for (long long i=(long long)(l)+1LL; i<=(long long)(r); ++i)
#define rep1_4(i, l, r, s) for (long long i=(long long)(l)+1LL; i<=(long long)(r); i+=(long long)(s))
#define overload_rep1(a, b, c, d, e, ...) e
#define rep1(...) overload_rep1(__VA_ARGS__, rep1_4, rep1_3, rep1_2, rep1_1)(__VA_ARGS__)

#define per_1(n) for (long long _=(long long)(n)-1LL; 0LL<=_; --_)
#define per_2(i, n) for (long long i=(long long)(n)-1LL; 0LL<=i; --i)
#define per_3(i, l, r) for (long long i=(long long)(r)-1LL; (long long)(l)<=i; --i)
#define per_4(i, l, r, s) for (long long i=(long long)(r)-1LL; (long long)(l)<=i; i-=(long long)(s))
#define overload_per(a, b, c, d, e, ...) e
#define per(...) overload_per(__VA_ARGS__, per_4, per_3, per_2, per_1)(__VA_ARGS__)

#define per1_1(n) for (long long _=(long long)(n); 0LL<_; --_)
#define per1_2(i, n) for (long long i=(long long)(n); 0LL<i; --i)
#define per1_3(i, l, r) for (long long i=(long long)(r); (long long)(l)<i; --i)
#define per1_4(i, l, r, s) for (long long i=(long long)(r); (long long)(l)<i; i-=(long long)(s))
#define overload_per1(a, b, c, d, e, ...) e
#define per1(...) overload_per1(__VA_ARGS__, per1_4, per1_3, per1_2, per1_1)(__VA_ARGS__)

#define range_1(v) for (auto& _ : (v))
#define range_2(i, v) for (auto& i : (v))
#define range_3(i, j, v) for (auto& [i, j] : (v))
#define overload_range(a, b, c, d, ...) d
#define range(...) overload_range(__VA_ARGS__, range_3, range_2, range_1)(__VA_ARGS__)

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define len(x) ssize(x)
#define elif else if
#define pb emplace_back
#define db pop_back
#define pf emplace_front
#define df pop_front
#define fi first
#define se second

#define Sort(v) sort((v).begin(), (v).end())
#define troS(v) sort((v).rbegin(), (v).rend())
#define Reverse(v) reverse((v).begin(), (v).end())
#define uniq(v) sort((v).begin(), (v).end()), (v).erase(unique((v).begin(), (v).end()), (v).end())
#define bit(x, i) (((x)>>(i))&1)

#define nextp(v) next_permutation((v).begin(), (v).end())
template <class T>
bool next_combination(T l, T r, int k) {
    T m = l + k;
    if (l==r || r==m || m==l) return false;
    T t = m;
    while (l != t) {
        t--;
        if (*t < *(r-1)) {
            T d = m;
            while (*d <=*t) d++;
            iter_swap(t, d);
            rotate(t+1, d+1, r);
            rotate(m, m+(r-d)-1, r);
            return true;
        }
    }
    rotate(l, m, r);
    return false;
}
#define nextc(v, k) next_combination((v).begin(), (v).end(), k)

#define Yes cout << "Yes\n"
#define No cout << "No\n"
#define YN(x) cout << ((x) ? "Yes\n" : "No\n")
#define O(x) cout << (x) << '\n'

#define ismid_1(x) true
template <class T, class U>
bool inner_ismid_2(T x, U r) { return T{}<=x && x<r; }
#define ismid_2(x, r) inner_ismid_2(x, r)
template <class T, class U, class V>
bool inner_ismid_3(T l, U x, V r) { return l<=x && x<r; }
#define ismid_3(l, x, r) inner_ismid_3(l, x, r)
#define overload_ismid(a, b, x, d, ...) d
#define ismid(...) overload_ismid(__VA_ARGS__, ismid_3, ismid_2, ismid_1)(__VA_ARGS__)

inline int popcnt(int x) { return __builtin_popcount((unsigned int)x); }
inline int popcnt(unsigned int x) { return __builtin_popcount(x); }
inline int popcnt(long long x) { return __builtin_popcountll(x); }
inline int popcnt(unsigned long long x) { return __builtin_popcountll(x); }
inline int topbit(int x) { return x==0 ? -1 : 31-__builtin_clz(x); }
inline int topbit(unsigned int x) { return x==0 ? -1 : 31-__builtin_clz(x); }
inline int topbit(long long x) { return x==0 ? -1 : 63-__builtin_clzll(x); }
inline int topbit(unsigned long long x) { return x==0 ? -1 : 63-__builtin_clzll(x); }

template<class T>
bool next_subset(T x, T& s) {
    if (s == T{}) return false;
    s = (s-1) & x;
    return true;
}

template <class T>
constexpr vector<T> enum_pow(T x, int n) {
    vector<T> re(n+1);
    re[0] = T{1};
    for (int i=1; i<=n; ++i) re[i] = re[i-1] * x;
    return re;
}

template <class T, class U>
inline T Pow(T x, U n) {
    T re = T{1};
    if (n < U{}) {
        x = T{1} / x;
        n = -n;
    }
    while (U{} < n) {
        if ((n & U{1}) == 1) re *= x;
        x *= x;
        n >>= 1;
    }
    return re;
}

template <class T, class U>
inline bool chmin(T& x, U y) {
    if (x <= y) return false;
    x = y;
    return true;
}
template <class T, class U>
inline bool chmax(T& x, U y) {
    if (y <= x) return false;
    x = y;
    return true;
}

template <class T, class U>
auto Min(T x, U y) {
    using R = common_type_t<T, U>;
    R a = x, b = y;
    return (b < a) ? b : a;
}
template<class T, class U, class ...Args>
auto Min(T x, U y, Args... args) { return Min(Min(x, y), args...); }
template <class T>
T Min(initializer_list<T> v) {
    assert(v.size());
    return *min_element(v.begin(), v.end());
}
template <class T, class U>
auto Max(T x, U y) {
    using R = common_type_t<T, U>;
    R a = x, b = y;
    return (a < b) ? b : a;
}
template<class T, class U, class ...Args>
auto Max(T x, U y, Args... args) { return Max(Max(x, y), args...); }
template <class T>
T Max(initializer_list<T> v) {
    assert(v.size());
    return *max_element(v.begin(), v.end());
}

template<typename T> struct is_string : false_type {};
template<typename Char, typename Traits, typename Alloc>
struct is_string<basic_string<Char,Traits,Alloc>> : true_type {};
template<typename T, typename = void>
struct is_iterable : false_type {};
template<typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : conditional_t<is_string<T>::value, false_type, true_type> {};
template<typename T, enable_if_t<!is_iterable<T>::value, nullptr_t> = nullptr>
auto Min(const T& x) { return x; }
template<typename T, enable_if_t<!is_iterable<T>::value, nullptr_t> = nullptr>
auto Max(const T& x) { return x; }
template<typename T, enable_if_t<!is_iterable<T>::value, nullptr_t> = nullptr>
auto Sum(const T& x) { return x; }
template<class A, class B>
auto Min(const pair<A,B>& p) {
    using R1 = decay_t<decltype(Min(p.first))>;
    using R2 = decay_t<decltype(Min(p.second))>;
    using R  = decay_t<common_type_t<R1, R2>>;
    R a = Min(p.first);
    R b = Min(p.second);
    return (b < a) ? b : a;
}
template<class A, class B>
auto Max(const pair<A,B>& p) {
    using R1 = decay_t<decltype(Max(p.first))>;
    using R2 = decay_t<decltype(Max(p.second))>;
    using R  = decay_t<common_type_t<R1, R2>>;
    R a = Max(p.first);
    R b = Max(p.second);
    return (a < b) ? b : a;
}
template<class A, class B>
auto Sum(const pair<A,B>& p) {
    using R1 = decay_t<decltype(Sum(p.first))>;
    using R2 = decay_t<decltype(Sum(p.second))>;
    using R  = decay_t<common_type_t<R1, R2>>;
    R res{};
    res += Sum(p.first);
    res += Sum(p.second);
    return res;
}
template<typename C, enable_if_t<is_iterable<C>::value, nullptr_t> = nullptr>
auto Min(const C& v) {
    assert(!v.empty());
    auto it = v.begin();
    auto re = Min(*it);
    for (++it; it!=v.end(); ++it) {
        auto v = Min(*it);
        if (v < re) re = v;
    }
    return re;
}
template<typename C, enable_if_t<is_iterable<C>::value, nullptr_t> = nullptr>
auto Max(const C& v) {
    assert(!v.empty());
    auto it = v.begin();
    auto re = Max(*it);
    for (++it; it != v.end(); ++it) {
        auto v = Max(*it);
        if (re < v) re = v;
    }
    return re;
}
template<typename C, enable_if_t<is_iterable<C>::value, nullptr_t> = nullptr>
auto Sum(const C& v) {
    using R = decay_t<decltype(Sum(*v.begin()))>;
    R re = R{};
    for (auto it=v.begin(); it!=v.end(); ++it) re += Sum(*it);
    return re;
}

template<class T, class U>
istream& operator>>(istream& s, pair<T, U>& p) {
    s >> p.first >> p.second;
    return s;
}
template<class T, class U>
ostream& operator<<(ostream& s, const pair<T, U>& p) {
    return s << p.first << ' ' << p.second;
}
template<class T>
istream& operator>>(istream& s, vector<T>& v) {
    for (auto& i : v) s >> i;
    return s;
}
template<class T>
ostream& operator<<(ostream& s, const vector<T>& v) {
    for (int i=0; i<ssize(v); i++) {
        if (i) s << ' ';
        s << v[i];
    }
    return s;
}

#ifdef poe
inline void debug_out() { cerr << '\n'; }
template<class T, class... Args>
void debug_out(const T& x, const Args&... args) {
    cerr << x;
    if constexpr (sizeof...(args)) cerr << ' ';
    debug_out(args...);
}
#endif

const vector<int> dxy = {0, 1, 0, -1, 0};
const vector<int> dx = {0, 1, 0, -1, 1, 1, -1, -1};
const vector<int> dy = {1, 0, -1, 0, 1, -1, 1, -1};
constexpr char nl = '\n';
constexpr char sp = ' ';
constexpr int INF = numeric_limits<int>::max()/2;
constexpr long long LINF = numeric_limits<long long>::max()/2;
template <class T>
constexpr T infty = numeric_limits<T>::is_integer ? (numeric_limits<T>::max()/2) : numeric_limits<T>::infinity();
constexpr long double eps = 1e-9;
const long double PI = acos(-1);
constexpr long long mod = 998244353;
constexpr long long MOD = 1000000007;

inline void IO() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

void solve();
