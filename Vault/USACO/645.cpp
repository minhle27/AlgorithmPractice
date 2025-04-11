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

ll area(ll x1, ll x2, ll y1, ll y2) { return abs(x2 - x1) * abs(y2 - y1); }

ll scan(const vector<pl> &cows, vector<pl> &pref, vector<pl> &suf) {
    int n = sz(cows);
    pref = vector<pl>(n);
    suf = vector<pl>(n);
    pref[0] = {cows[0].second, cows[0].second};
    for (int i = 1; i < n; i++) {
        pref[i].first = min(cows[i].second, pref[i - 1].first);
        pref[i].second = max(cows[i].second, pref[i - 1].second);
    }

    suf[n - 1] = {cows[n - 1].second, cows[n - 1].second};
    for (int i = n - 2; i >= 0; i--) {
        suf[i].first = min(cows[i].second, suf[i + 1].first);
        suf[i].second = max(cows[i].second, suf[i + 1].second);
    }
    ll minarea = 1e18 + 7;
    for (int i = 0; i < n - 1; i++) {
        if (cows[i].first == cows[i + 1].first)
            continue;
        ll left = abs(cows[0].first - cows[i].first) *
                  abs(pref[i].first - pref[i].second);
        ll right = abs(cows[i + 1].first - cows[n - 1].first) *
                   abs(suf[i + 1].first - suf[i + 1].second);
        ckmin(minarea, left + right);
    }
    return minarea;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);

    ll n;
    cin >> n;
    vector<pl> cows;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        cows.push_back({x, y});
    }

    sort(cows.begin(), cows.end());
    vector<pl> pref, suf;
    ll vertical_min = scan(cows, pref, suf); // vertical scan

    ll initial = area(cows[0].first, cows[n - 1].first, pref[n - 1].first,
                      pref[n - 1].second);

    for (int i = 0; i < n; i++)
        swap(cows[i].first, cows[i].second);

    sort(cows.begin(), cows.end());
    ll horizontal_min = scan(cows, pref, suf); // horizontal scan

    cout << initial - min(vertical_min, horizontal_min) << endl;

    return 0;
}
