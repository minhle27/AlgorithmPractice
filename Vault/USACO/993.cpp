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
const int INF = 1e9 + 7;
vi mooney;
const int max_t = 1005;
const int max_n = 1005;
vector<vi> g;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    cin >> n >> m >> c;
    mooney.resize(n + 1);
    g = vector<vi>(n + 1);

    for (int i = 1; i <= n; i++){
        cin >> mooney[i];
    }
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    vector<vi> dp(max_t, vi(max_n, -1));
    dp[0][1] = 0;
    int ans = 0;
    for (int t = 0; t <= 1000; t++){
        for (int i = 1; i <= n; i++){
            if (dp[t][i] != -1){
                for (auto u : g[i]){
                    dp[t + 1][u] = max(dp[t + 1][u], dp[t][i] + mooney[u]);
                }
            }
        }
        ans = max(ans, dp[t][1] - c * t * t);
    }
    
    cout << ans << endl;
    return 0;
}