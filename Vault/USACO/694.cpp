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

int n, k;
const int INF = 1e9 + 7;
const int maxn = 1e5 + 7;
const int maxk = 27;
int dp[maxn][maxk][3];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    cin >> n >> k;
    vi a(n + 1);
    for (int i = 1; i <= n; i++){
        char c; cin >> c;
        if (c == 'H') a[i] = 0;
        else if (c == 'P') a[i] = 1;
        else if (c == 'S') a[i] = 2;
    }

    memset(dp[0], 0, sizeof(dp[0]));

    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= k; j++){
            for (int t = 0; t < 3; t++){
                int win = 0;
                if (t - a[i] == 1 || t - a[i] == -2) win++;
                dp[i][j][t] = dp[i - 1][j][t];
                if (j > 0){
                    dp[i][j][t] = max({dp[i][j][t], dp[i - 1][j - 1][(t + 1) % 3], dp[i - 1][j - 1][(t + 2) % 3]});
                }
                dp[i][j][t] += win;
            }
        }
    }

    int res = 0;
    for (int t = 0; t < 3; t++){
        res = max(res, dp[n][k][t]);
    }

    cout << res << endl;

    
    return 0;
}