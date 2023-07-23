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

int n;
const int maxn = 105;
int x[maxn];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int maxsum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        maxsum += x[i];
    }

    vector<vi> dp(n + 10, vi(maxsum + 10, 0));
    dp[0][0] = 1;

    ll res = 0;
    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= maxsum; j++){
            dp[i][j] |= dp[i - 1][j];
            if (j >= x[i]) dp[i][j] |= dp[i - 1][j - x[i]];
            if (dp[i][j] && i == n) res++;
        }
    }

    cout << res - 1 << endl;
    for (int i = 1; i <= maxsum; i++){
        if (dp[n][i]) cout << i << " ";
    }
    
    return 0;
}