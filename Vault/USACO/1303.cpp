#include <algorithm>
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

bool possible(const pi &pos1, int t1, const pi &pos2, int t2) {
    ll dx = pos1.first - pos2.first;
    ll dy = pos1.second - pos2.second;
    ll dist = dx * dx + dy * dy;
    ll dt = (ll)t2 - t1;
    return dist <= dt * dt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int g, n;
    cin >> g >> n;

    vi times;
    map<int, pi> locs;
    for (int i = 0; i < g; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        times.push_back(t);
        locs[t] = {x, y};
    }

    sort(times.begin(), times.end());
    int res = 0;
    for (int i = 0; i < n; i++) {
        int x, y, t;
        cin >> x >> y >> t;

        auto lowerit = lower_bound(times.begin(), times.end(), t);

        if (lowerit == times.begin()) {
            if (!possible(locs[times[0]], times[0], {x, y}, t)) {
                res++;
            }
        } else if (lowerit == times.end()) {
            if (!possible(locs[times[g - 1]], times[g - 1], {x, y}, t)) {
                res++;
            }
        } else {
            auto prev = lowerit - 1;
            bool flag1 = possible(locs[*prev], *prev, {x, y}, t);
            bool flag2 = possible(locs[*lowerit], *lowerit, {x, y}, t);

            if (!flag1 || !flag2)
                res++;
        }
    }
    cout << res << endl;

    return 0;
}
