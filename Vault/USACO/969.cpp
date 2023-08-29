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
int n, m;
const int maxn = 1007;
const int INF = 1e9 + 7;

struct Edge {
    int v;
    int c;
    int f;
};

vector<double> d;
vector<vector<Edge>> g;
vi min_flow;
using pdi = pair<double, int>;

void dijkstra(int s) {
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    pq.push({0, s});
    d[s] = 0;
    min_flow[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        double du = pq.top().first;
        pq.pop();

        if (du != d[u]) continue;

        for (auto e : g[u]) {
            int v = e.v;
            int c = e.c;
            int f = e.f;

            double opt_du = 0;
            if (min_flow[u] == 0) {
                opt_du = (d[u] + c) / (f * 1.0);
            } 
            else {
                assert(min_flow[u] != INF);
                opt_du = (d[u] * min_flow[u] + c) * 1.0 / min(min_flow[u], f);
            }
            
            if (d[v] > opt_du) {
                d[v] = opt_du;
                pq.push({d[v], v});
                if (min_flow[u] == 0) min_flow[v] = f;
                else min_flow[v] = min(min_flow[u], f);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("debug.log", "w", stderr);
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);

    cin >> n >> m;
    d.resize(n + 7, INF);
    g.resize(n + 7);
    min_flow.resize(n + 7, INF);
    for (int i = 0; i < m; i++) {
        int a, b, c, f;
        cin >> a >> b >> c >> f;
        g[a].PB({b, c, f});
        g[b].PB({a, c, f});
    }

    dijkstra(1);

    int res = (1.0 / d[n]) * 1e6;
    cout << res << endl;
    
    return 0;
}