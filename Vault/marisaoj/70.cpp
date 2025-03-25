#include <bits/stdc++.h>
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

// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; 
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, m;
    cin >> n >> q >> m;
    vector<pi> queries(q + 1);
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = {l, r};
    }

    vi diffops(q + 2, 0);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        diffops[x]++;
        diffops[y + 1]--;
    }

    for (int i = 1; i <= q; i++) {
        diffops[i] += diffops[i - 1];
    }

    vi arr(n + 2, 0);
    for (int i = 1; i <= q; i++) {
        int l = queries[i].first;
        int r = queries[i].second;

        arr[l] += diffops[i];
        arr[r + 1] -= diffops[i];
    }

    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
        cout << arr[i] << " ";
    }
    cout << endl;


    return 0;
}



