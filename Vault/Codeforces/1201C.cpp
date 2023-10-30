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

bool f(ll x){
    ll steps = 0;
    for (int i = (n + 1) / 2 - 1; i < n; i++){
        steps += max(ll(0), x - a[i]);
    }
    return steps <= k;
}

ll binary_search(int lo, int hi) {
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) lo = mid;
        else hi = mid - 1;
    }

    if (f(lo) == false) return -1;

    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    a.resize(n);
    for (ll &x : a) cin >> x;
    sort(a.begin(), a.end());
    ll med = a[(n + 1) / 2 - 1];

    cout << binary_search(med, med + k) << endl;

    return 0;
}