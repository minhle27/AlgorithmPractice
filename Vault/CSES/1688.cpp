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
const int maxn = 2 * 1e5 + 7;
const int inf = 1e9 + 7;
vector<vi> g(maxn);

struct LCA {
    vi height, euler, first, st;
    int n;

    LCA(int _n, int root = 0) {
        n = _n;
        height.resize(n);
        first.resize(n);
        euler.reserve(2 * n);
        dfs(root, -1);
        int m = sz(euler);
        st.resize(4 * m);
        build(1, 0, m - 1);
    }

    // build euler path
    void dfs(int cur, int par, int h = 0) {
        height[cur] = h;
        first[cur] = sz(euler);
        euler.push_back(cur);
        for (auto next : g[cur]) {
            if (next == par) continue;
            dfs(next, cur, h + 1);
            euler.push_back(cur);
        }
    }

    // Segtree
    void build(int id, int l, int r) { // O(n)
        if (l == r) {
            st[id] = euler[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(2 * id, l, mid);
        build(2 * id + 1, mid + 1, r);
        int lchild = st[2 * id], rchild = st[2 * id  + 1];
        st[id] = (height[lchild] < height[rchild]) ? lchild : rchild;
    }

    int get(int id, int l, int r, int u, int v) { // O(log n)
        if (l >  v || r <  u) return -inf;
        if (l >= u && r <= v) return st[id];

        int mid = (l + r) >> 1;
        int get1 = get(2 * id, l, mid, u, v);
        int get2 = get(2 * id + 1, mid + 1, r, u, v);
        if (get1 == -inf) return get2;
        if (get2 == -inf) return get1;
        return height[get1] < height[get2] ? get1 : get2;
    }
    

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right) swap(left, right);
        return get(1, 0, sz(euler) - 1, left, right);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("debug.log", "w", stderr);
    cin >> n >> q;
    for (int i = 1; i <= n - 1; i++) {
        int boss; cin >> boss;
        boss--;
        g[i].PB(boss); g[boss].PB(i);
    }

    LCA tree(n);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << tree.lca(a, b) + 1 << endl;
    }
    
    return 0;
}