#include <bits/stdc++.h>
#include <iomanip>
#include <queue>
using namespace std;

using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using vi = vector<int>;
using vl = vector<ll>;
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
const int maxn = 755;
const int maxm = 1005;
vector<pi> buildings;
vector<vector<pair<int, double>>> g;
vector<vector<bool>> am;
int n, m;

vi taken;
priority_queue<pair<double, int>> pq;

double dis(int a, int b) {
    pi p1 = buildings[a - 1];
    pi p2 = buildings[b - 1];
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

void reset() {
    buildings.clear();
    g = vector<vector<pair<int, double>>>(n + 1);
    am = vector<vector<bool>>(n + 1, vector<bool> (n + 1, false));
    taken = vi (n + 1, 0);
    pq = priority_queue<pair<double, int>> ();
}

void process(int u) {
    taken[u] = 1;
    for (auto &[v, w] : g[u]) {
        if (!taken[v]) {
            pq.push({-w, -v});
        }
    }
}

double prim() {
    double mst = 0;
    int num_taken = 0;
    process(1);
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        w = -w; u = -u;
        if (taken[u]) continue;
        mst += w;
        process(u);
        ++num_taken;
        if (num_taken == n - 1) break;
    }
    return mst;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("debug.log", "w", stderr);
    while (cin >> n) {
        reset();
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            buildings.push_back({x, y});
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            am[a][b] = true;
            am[b][a] = true;
        }
        for (int i = 1; i <= n - 1; i++) {
            for (int j = i + 1; j <= n; j++) {
                double dis_ij;
                if (!am[i][j]) {
                    dis_ij = dis(i, j);
                } else {
                    dis_ij = 0;
                }
                g[i].push_back({j, dis_ij});
                g[j].push_back({i, dis_ij});
            }
        }
        double res = prim();
        cout << fixed << setprecision(2) << res << endl;
    }


    return 0;
}
