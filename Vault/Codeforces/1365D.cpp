#include <bits/stdc++.h>
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

const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
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

const int MAXN = 50;
bool visited[MAXN][MAXN];

int n, m;
bool isValid(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

void dfs1(pi s, vector<string> &g) {
    visited[s.first][s.second] = true;
    for (int i = 0; i < 4; i++) {
        int u = s.first + dx[i];
        int v = s.second + dy[i];
        if (!isValid(u, v))
            continue;
        if (!visited[u][v] && g[u][v] == 'B') {
            dfs1({u, v}, g);
        } else if (g[u][v] == '.') {
            g[u][v] = '#';
        }
    }
}

bool dfs2(pi s, const vector<string> &g, int &gcnt) {
    visited[s.first][s.second] = true;
    for (int i = 0; i < 4; i++) {
        int u = s.first + dx[i];
        int v = s.second + dy[i];
        if (!isValid(u, v) || g[u][v] == '#')
            continue;
        if (g[u][v] == 'B')
            return false;

        if (!visited[u][v]) {
            if (g[u][v] == 'G')
                gcnt++;
            if (!dfs2({u, v}, g, gcnt))
                return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vector<string> g(n);
        for (int i = 0; i < n; i++) {
            cin >> g[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }

        int gtotal = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'G')
                    gtotal++;
                else if (g[i][j] == 'B' && !visited[i][j]) {
                    dfs1({i, j}, g);
                }
            }
        }
        int gcnt = 0;
        bool flag = dfs2({n - 1, m - 1}, g, gcnt);
        if (gtotal == 0) {
            cout << "Yes" << endl;
        } else {
            if (flag && gtotal == gcnt) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}
