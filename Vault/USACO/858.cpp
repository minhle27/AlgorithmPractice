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

int n, m, c;
vi times;

bool ok(int maxtime) {
    int i = 0;
    int buses = m;
    while (buses > 0) {
        int mintime = times[i];
        int curcap = 0;
        while (times[i] - mintime <= maxtime && curcap < c && i < n) {
            i++;
            curcap++;
        }
        buses--;
    }
    return i == n;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    cin >> n >> m >> c;
    times.resize(n);
    for (int &x : times) cin >> x;
    sort(times.begin(), times.end());
    
    int lo = 0, hi = 1000000005, ans = 0;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (ok(mid)) {
            ans = mid; hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    if (ok(lo)) ans = lo;
    cout << ans << endl;
    
    return 0;
}