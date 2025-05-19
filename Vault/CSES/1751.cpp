#include <bits/stdc++.h>
#include <unordered_set>
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

vi f, res;
vector<bool> visited;

int n;

int distToEntry(int x, int entry, int cyclen) {
    if (x == entry)
        return 0;

    int neidist = distToEntry(f[x], entry, cyclen);
    res[x] = 1 + neidist + cyclen;
    return 1 + neidist;
}

void floyd(int x) {
    int a = x;
    int b = x;
    do {
        a = f[a];
        b = f[f[b]];
        if (res[a] != -1) {
            distToEntry(x, a, res[a]);
            return;
        }
    } while (a != b);

    a = x;
    while (a != b) {
        a = f[a];
        b = f[b];
    }
    int entry = a;
    a = entry;
    int cyclen = 0;
    do {
        a = f[a];
        cyclen++;
    } while (a != entry);

    a = entry;
    do {
        res[a] = cyclen;
        a = f[a];
    } while (a != entry);

    a = x;
    distToEntry(x, entry, cyclen);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    f = vi(n + 1);
    res = vi(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        cin >> f[i];
    }

    for (int i = 1; i <= n; i++) {
        if (res[i] == -1) {
            floyd(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
