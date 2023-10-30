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

int t, n;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n;
        vi a(n);
        vector<vi> dp(n, vi(2, 0));
        for (int &x : a) cin >> x;

        if (a[n - 1] == 1) dp[n - 1][0] = 1;
        if (a[n - 2] == 1) dp[n - 2][0] = 1;
        for (int i = n - 3; i >= 0; i--){
            if (a[i] == 1){
                if (a[i + 1] == 0) dp[i][0] = min(dp[i + 1][1], dp[i + 2][1]) + 1;
                else dp[i][0] = min(dp[i + 1][1] + 1, dp[i + 2][1] + 2);
            }
            else {
                if (a[i + 1] == 0) dp[i][0] = min(dp[i + 1][1], dp[i + 2][1]);
                else dp[i][0] = min(dp[i + 1][1], dp[i + 2][1] + 1);
            }
            dp[i][1] = min(dp[i + 1][0], dp[i + 2][0]);
        }

        cout << dp[0][0] << endl;
    }

    
    return 0;
}