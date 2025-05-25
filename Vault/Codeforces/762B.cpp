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
#define tcT template<class T

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
template<class T>
using pqg = priority_queue<T, vector<T>, greater<T>>; // minheap

tcT > bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
} // set a = min(a,b)
tcT > bool ckmax(T& a, const T& b) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;

    int m;
    cin >> m;
    vi usb;
    vi ps2;
    for (int i = 0; i < m; i++) {
        int price;
        string type;
        cin >> price >> type;
        if (type == "USB") {
            usb.push_back(price);
        } else {
            ps2.push_back(price);
        }
    }

    sort(usb.begin(), usb.end());
    sort(ps2.begin(), ps2.end());

    ll cost = 0;

    // buy usb
    int buy_a = 0;
    buy_a += min(a, sz(usb));
    for (int i = 0; i < buy_a; i++) {
        cost += usb[i];
    }

    // buy ps2
    int buy_b = min(b, sz(ps2));
    for (int i = 0; i < buy_b; i++) {
        cost += ps2[i];
    }

    int p1 = buy_a;
    int p2 = buy_b;

    int buy_c = 0;
    while (p1 < sz(usb) || p2 < sz(ps2)) {
        if (buy_c == c)
            break;
        if (p1 < sz(usb) && p2 < sz(ps2)) {
            buy_c++;
            if (usb[p1] < ps2[p2]) {
                cost += usb[p1];
                p1++;
            } else {
                cost += ps2[p2];
                p2++;
            }
        } else if (p1 < sz(usb)) {
            buy_c++;
            cost += usb[p1];
            p1++;
        } else {
            buy_c++;
            cost += ps2[p2];
            p2++;
        }
    }
    cout << buy_a + buy_b + buy_c << " " << cost << endl;

    return 0;
}
