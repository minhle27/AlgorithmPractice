#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pi;
typedef tuple<int, int, int> iii;

#define f first
#define s second
#define PB push_back
#define MP make_pair

#define LSOne(S) ((S) & -(S))
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n, l, r, x;
const int INF = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> l >> r >> x;
    vi c(n);
    for (int &k : c) cin >> k;
    
    ll res = 0;
    for (int mask = 0; mask < (1 << n); mask++){
        if (__builtin_popcount(mask) < 2) continue;
        int total = 0;
        int maxdif = -1; int mindif = INF;
        for (int i = 0; i < n; i++){
            if (mask & (1 << i)) {
                total += c[i];
                maxdif = max(maxdif, c[i]);
                mindif = min(mindif, c[i]);
            }
        }
        if (total >= l && total <= r && maxdif - mindif >= x) {
            res++;
        }
    }
    cout << res << endl;
    
    return 0;
}