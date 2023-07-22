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


const int maxn = 1e5 + 7;
const int mod = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vi> dp(n, vi(m + 1, 0));
    int x0; cin >> x0;

    // base of dp table
    if (x0 == 0){
        fill(dp[0].begin(), dp[0].end(), 1);
    }
    else {
        dp[0][x0] = 1;
    }

    for (int i = 1; i < n; i++){
        int x; cin >> x;
        if (x == 0){
            for (int j = 1; j <= m; j++){
                for (int k : {j - 1, j, j + 1}){
                    if (1 <= k && k <= m){
                        (dp[i][j] += dp[i - 1][k]) %= mod;
                    }
                }
            }
        } else {
            for (int k : {x-1,x,x+1}) {
	            if (k >= 1 && k <= m) {
	                (dp[i][x] += dp[i-1][k]) %= mod;
	            }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++){
        ans += dp[n - 1][i];
        ans %= mod;
    }

    cout << ans << endl;
    
    return 0;
}