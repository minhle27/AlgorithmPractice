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
 
int N, X;
vl a;
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> N >> X;
    a.resize(N);
    for (ll &x : a) cin >> x;
 
    sort(a.begin(), a.end());
    ll res = 0; ll ind = 0;
    while (X > 0 && ind < N){
        X -= a[ind]; ind++;
        if (X >= 0) res++;
    }
 
    cout << res << endl;
    
    return 0;
}