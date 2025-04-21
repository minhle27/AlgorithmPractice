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

const int MAXN = 102;
bool islit[MAXN][MAXN];
bool visited[MAXN][MAXN];
map<pi, vector<pi>> link;

int n, m;
bool isValid(int u, int v) { return 1 <= u && u <= n && 1 <= v && v <= n; }

bool checkAdj(int u, int v) {
    for (int i = 0; i < 4; i++) {
        int x = u + dx[i];
        int y = v + dy[i];
        if (isValid(x, y) && visited[x][y]) {
            return true;
        }
    }
    return false;
}

void bfs(pi s) {
    visited[s.first][s.second] = true;
    queue<pi> q;
    q.push(s);
    while (!q.empty()) {
        pi u = q.front();
        q.pop();
        if (link.count(u) != 0) {
            for (const pi &room : link[u]) {
                islit[room.first][room.second] = true;
                if (checkAdj(room.first, room.second)) {
                    if (!visited[room.first][room.second]) {
                        visited[room.first][room.second] = true;
                        q.push(room);
                    }
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            int x = u.first + dx[i];
            int y = u.second + dy[i];
            if (isValid(x, y) && islit[x][y] && !visited[x][y]) {
                visited[x][y] = true;
                q.push({x, y});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        link[{x, y}].push_back({a, b});
    }

    memset(islit, 0, sizeof(islit));
    memset(visited, 0, sizeof(visited));

    islit[1][1] = true;
    bfs({1, 1});

    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (islit[i][j])
                res++;
        }
    }
    cout << res << endl;

    return 0;
}
