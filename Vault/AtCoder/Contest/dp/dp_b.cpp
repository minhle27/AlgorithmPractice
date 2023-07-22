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

int cost(int h1, int h2){
    return abs(h1 - h2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    vi h(n);
    for (int &x : h) cin >> x;
    vi dp(n + 1, INF);
    dp[1] = 0;
    for (int i = 2; i <= n; i++){
        for (int j = 1; j <= k; j++){
            if (i - j >= 1){
                dp[i] = min(dp[i], dp[i - j] + cost(h[i - j - 1], h[i - 1]));
            }
        }
    }

    cout << dp[n] << endl;
    
    return 0;
}