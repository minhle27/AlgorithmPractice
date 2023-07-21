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

ll N, tmax;
vl d;

bool P(ll k){
    priority_queue<ll, vl, greater<ll>> pq;
    ll lasttime = 0;
    for (int i = 1; i <= N; i++){
        if (pq.size() == k){
            lasttime = pq.top();
            pq.pop();
        }
        if (lasttime + d[i] > tmax) return false;
        pq.push(lasttime + d[i]);
    }
    return true;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    cin >> N >> tmax;
    d.resize(N + 1); d[0] = 0;
    for (int i = 1; i <= N; i++){
        cin >> d[i];
    }

    ll lo = 1, hi = N, ans = 0;
    while (lo <= hi){
        ll mid = lo + (hi - lo) / 2;
        if (P(mid)){
            ans = mid; 
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}