#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef tuple<int, int, int> iii;

#define PB push_back
#define MP make_pair

#define LSOne(S) ((S) & -(S))
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define tcT template<class T

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

// const int MOD = (int)1e9+7;
// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>; // minheap

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

// bitwise ops
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0); 
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

// DEBUGING TEMPLETE ////////////////////////////////////////////////////////////////////////
// src: https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
#define db(val) "["#val" = "<<(val)<<"] "
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#ifdef LOCAL_DEBUG   
#   define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#   define DB() debug_block CONCAT(dbbl, __LINE__)
    int __db_level = 0;
    struct debug_block {
        debug_block() { clog << "{" << endl; ++__db_level; }
        ~debug_block() { --__db_level; clog << "}" << endl; }
    };
#else
#   define clog if (0) cerr
#   define DB(...)
#endif

// for printing std::pair
template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}

// for printing collection
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
}

// for printing std::tuple
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}
// g++ -std=c++17 -O2 -DLOCAL_DEBUG name.cpp -o name -Wall
// g++ -std=c++17 -O2 name.cpp -o name -Wall

// ACTUAL SOLUTION START HERE ////////////////////////////////////////////////////////////////
struct node {
    int optimal, open, close;

    static node base() { return {0, 0, 0}; };

    static node merge(const node& left, const node& right) {
        node res;
        int new_match = min(left.open, right.close);
        res.optimal = left.optimal + right.optimal + new_match * 2;

        res.open = (left.open - new_match) + right.open;
        res.close = left.close + (right.close - new_match);

        return res;
    }
};

string s;
int q;
const int maxn = 1e6 + 7;
node st[4 * maxn];

// 0 <= l <= r <= n - 1
void build(int id, int l, int r) {
    if (l == r) {
        if (s[l - 1] == '(') st[id] = {0, 1, 0};
        else st[id] = {0, 0, 1};
        return;
    }

    int mid = (l + r) >> 1;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);

    st[id] = node::merge(st[2 * id], st[2 * id + 1]);
}

node get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return node::base();
    if (l >= u && r <= v) return st[id];

    int mid = (l + r) >> 1;
    node get1 = get(2 * id, l, mid, u, v);
    node get2 = get(2 * id + 1, mid + 1, r, u, v);
    return node::merge(get1, get2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("debug.log", "w", stderr);
    cin >> s >> q;

    build(1, 1, sz(s));
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        node res = get(1, 1, sz(s), l, r);
        cout << res.optimal << endl;
    }
    
    return 0;
}