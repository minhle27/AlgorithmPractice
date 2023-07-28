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
vector<pi> m;
const int maxn = 1e4 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        m.PB({a, b});
    }
    sort(m.begin(), m.end());

    vi dp(n + 1, 0);

    for (int i = 0; i <= n - 1; i++){
        dp[i] = m[i].s - m[i].f;
        for (int j = 0; j < i; j++){
            if (m[j].s <= m[i].f && dp[i] < dp[j] + m[i].s - m[i].f) {
                dp[i] = dp[j] + m[i].s - m[i].f;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++){
        res = max(res, dp[i]);
    }

    cout << res << endl;
    
    return 0;
}