#include <bits/stdc++.h>
#include <climits>
using namespace std;

using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using iii = tuple<int, int, int>;

#define PB push_back
#define MP make_pair
#define LSOne(S) ((S) & -(S))
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define tcT template <class T

#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; i--)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; i++)
#define DEBUG(x)                                                               \
    {                                                                          \
        cout << #x << " = ";                                                   \
        cout << (x) << endl;                                                   \
    }
#define PR(a, n)                                                               \
    {                                                                          \
        cout << #a << " = ";                                                   \
        FOR(_, 1, n) cout << a[_] << ' ';                                      \
        cout << endl;                                                          \
    }
#define PR0(a, n)                                                              \
    {                                                                          \
        cout << #a << " = ";                                                   \
        REP(_, n) cout << a[_] << ' ';                                         \
        cout << endl;                                                          \
    }

// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1};
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>; // minheap

tcT > bool ckmin(T &a, const T &b) {
    return b < a ? a = b, 1 : 0;
} // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
    return a < b ? a = b, 1 : 0;
} // set a = max(a,b)

tcT > T gcd(T a, T b) {
    T r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
tcT > T lcm(T a, T b) { return a / gcd(a, b) * b; }

ll cdiv(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b);
} // divide a by b rounded up
ll fdiv(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
} // divide a by b rounded down

// bitwise ops
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) {                                // assert(x >= 0);
    return x == 0 ? 0 : 31 - __builtin_clz(x);
} // floor(log2(x))
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

void dfs(int s, const vector<vi> &g, vector<bool> &visited, int curcomp,
         vi &labels) {
    visited[s] = true;
    labels[s] = curcomp;
    for (int nei : g[s]) {
        if (!visited[nei]) {
            dfs(nei, g, visited, curcomp, labels);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vi> g(n + 1);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<bool> visited(n + 1, false);
        int curcomp = 0;
        vi labels(n + 1);
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i, g, visited, curcomp, labels);
                curcomp++;
            }
        }
        vector<vi> comps(curcomp);
        for (int i = 1; i <= n; i++) {
            comps[labels[i]].push_back(i);
        }
        vi dist(curcomp, INT_MAX);
        int j = 0;
        vi &startcomp = comps[labels[1]];
        for (int i = 1; i <= n; i++) {
            while (j + 1 < sz(startcomp) && startcomp[j + 1] <= i) {
                j++;
            }
            int curmin = abs(i - startcomp[j]);
            if (startcomp[j] < i && j < sz(startcomp) - 1)
                ckmin(curmin, abs(i - startcomp[j + 1]));
            ckmin(dist[labels[i]], curmin);
        }

        j = 0;
        vi dist2(curcomp, INT_MAX);
        vi &endcomp = comps[labels[n]];
        for (int i = 1; i <= n; i++) {
            while (j + 1 < sz(endcomp) && endcomp[j + 1] < i) {
                j++;
            }
            int curmin = abs(i - endcomp[j]);
            if (endcomp[j] < i && j < sz(endcomp) - 1)
                ckmin(curmin, abs(i - endcomp[j + 1]));
            ckmin(dist2[labels[i]], curmin);
        }

        ll cost = 1e15;
        for (int i = 0; i < curcomp; i++) {
            ckmin(cost, (ll)dist[i] * dist[i] + (ll)dist2[i] * dist2[i]);
        }
        cout << cost << endl;
    }

    return 0;
}
