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

ll n;

vl psum(const vl &a){
    vl psum(sz(a) + 1);
    for (ll i = 0; i < sz(a); i++) {
        psum[i + 1] = (psum[i] + a[i]) % n;
        if (psum[i + 1] < 0) psum[i + 1] += n;
    }
    return psum;
}

ll nc2(ll n){
    return n * (n - 1) / 2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vl a(n);
    for (ll &x : a) cin >> x;
    vl pref = psum(a);
    
    vl cnt(n, 0);
    for (ll i = 1; i <= n; i++){
        cnt[pref[i]]++;
    }

    ll res = 0;
    for (ll i = 0; i < n; i++){
        if (cnt[i] > 1) res += nc2(cnt[i]);
        if (i == 0){
            res += cnt[i];
        }
    }

    cout << res << endl;

    return 0;
}