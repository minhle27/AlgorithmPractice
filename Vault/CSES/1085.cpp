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

ll n, k;
vl a;

bool ok(ll m){
    ll min_div = 0;
    ll cur = 0;
    for (int i = 0; i < n; i++){
        if (cur + a[i] <= m){
            cur += a[i];
        }
        else {
            min_div++;
            cur = a[i];
        }
    }
    min_div++;
    return min_div <= k;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    a.resize(n);
    for (ll &x : a) cin >> x;

    ll lo = *max_element(a.begin(), a.end()), hi = 1e18, ans = 0;

    while (lo <= hi){
        ll mid = lo + (hi - lo) / 2;
        if (ok(mid)){
            hi = mid - 1;
            ans = mid;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans << endl;
    
    return 0;
}