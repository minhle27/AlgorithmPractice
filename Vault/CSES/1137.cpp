#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;
using iii = tuple<int, int, int>;

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

tcT> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
tcT> T lcm(T a, T b) { return a / gcd(a, b) * b; }

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
int n, q;

template<
    typename T  
> struct FT {
    FT(int _n) : n(_n), f(_n + 1) {}

    // a[u] += val
    void update(int u, T val) {
        assert(0 <= u && u < n);
        ++u;
        for (; u <= n; u += u & -u) {
            f[u] += val;
        }
    }

    // return a[0] + .. + a[u-1]
    T get(int u) const {
        assert(0 <= u && u <= n);
        T res = 0;
        for (; u > 0; u -= u & -u) {
            res += f[u];
        }
        return res;
    }

    // return a[l] + .. + a[r-1]
    T get(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return 0;  // empty
        return get(r) - get(l);
    }

    void reset() {
        std::fill(f.begin(), f.end(), T(0));
    }

    int lower_bound(T sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(f) && f[pos + pw-1] < sum)
				pos += pw, sum -= f[pos-1];
		}
		return pos;
	}

    int n;
    vector<T> f;
};

const int maxn = 2 * 1e5 + 7;
vector<vi> g(maxn);
vector<int> start;
vector<int> en;
int timer = 0;

void euler_tour(int at, int prev) {
	start[at] = timer++;
	for (int n : g[at]) {
		if (n != prev) { euler_tour(n, at); }
	}
	en[at] = timer;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("debug.log", "w", stderr);
    cin >> n >> q;
    vi vals(n + 7);
    for (int i = 1; i <= n; i++) cin >> vals[i];

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].PB(b); g[b].PB(a);
    }
    
    start.resize(n + 2, 0);
    en.resize(n + 2, 0);
    euler_tour(1, -1);

    FT<ll> ft(n + 1);
    for (int i = 1; i <= n; i++) {
        ft.update(start[i], vals[i]);
    }
    
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            ft.update(start[s], x - vals[s]);
            vals[s] = x;
        }
        else {
            int s; cin >> s;
            ll res = ft.get(start[s], en[s]);
            cout << res << endl;
        }
    }

    return 0;
}