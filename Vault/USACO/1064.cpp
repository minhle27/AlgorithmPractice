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

pi intersect(const vi& ecow, const vi& ncow) {
    if (ecow[0] >= ncow[1] && ecow[1] <= ncow[0]) {
        return {ncow[0], ecow[0]};
    }
    return {-1, -1};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vi> east;
    vector<vi> north;
    vi res(n);
    for (int i = 0; i < n; i++) {
        char dir;
        int a, b;
        cin >> dir >> a >> b;
        if (dir == 'E') {
            east.push_back({b, a, true, i});
        } else {
            north.push_back({a, b, true, i});
        }
    }

    sort(east.begin(), east.end());
    sort(north.begin(), north.end());

    for (int i = 0; i < sz(north); i++) {
        vi& n_cow = north[i];
        for (int j = 0; j < sz(east); j++) {
            vi& e_cow = east[j];
            if (!e_cow[2] || !n_cow[2])
                continue;

            pi inp = intersect(e_cow, n_cow);

            if (inp.first != -1) {
                int distn = inp.second - n_cow[1];
                int diste = inp.first - e_cow[1];
                if (distn < diste) {
                    e_cow[2] = false;
                    res[n_cow[3]] += res[e_cow[3]];
                    res[n_cow[3]]++;
                } else if (distn > diste) {
                    n_cow[2] = false;
                    res[e_cow[3]] += res[n_cow[3]];
                    res[e_cow[3]]++;
                }
            }
            if (!n_cow[2])
                break;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << res[i] << endl;
    }

    return 0;
}
