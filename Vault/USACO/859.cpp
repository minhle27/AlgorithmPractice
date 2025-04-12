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

struct Compare {
    bool operator()(const array<int, 3> &a, const array<int, 3> &b) const {
        return a[2] > b[2];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    int n;
    cin >> n;
    vector<array<int, 3>> cows;
    for (int i = 0; i < n; i++) {
        int a, t;
        cin >> a >> t;
        cows.push_back({a, t, i + 1});
    }
    sort(cows.begin(), cows.end());
    int k = 0;
    int curtime = cows[0][0];
    priority_queue<array<int, 3>, vector<array<int, 3>>, Compare> pq;
    while (k < n && cows[k][0] <= curtime) {
        pq.push(cows[k]);
        k++;
    }

    int res = -1;
    while (!pq.empty() || k < n) {
        if (pq.empty()) {
            curtime = cows[k][0];
            while (k < n && cows[k][0] <= curtime) {
                pq.push(cows[k]);
                k++;
            }
        }
        auto top = pq.top();
        pq.pop();
        ckmax(res, curtime - top[0]);
        curtime += top[1];
        while (k < n && cows[k][0] <= curtime) {
            pq.push(cows[k]);
            k++;
        }
    }
    cout << res << endl;

    return 0;
}
