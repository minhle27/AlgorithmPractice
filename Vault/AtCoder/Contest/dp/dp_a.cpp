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
int dp[maxn];
int N;
vi h;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N; h.resize(N);
    for (int i = 1; i <= N; i++){
        cin >> h[i];
    }

    memset(dp, 0, sizeof(dp));
    dp[2] = abs(h[2] - h[1]);
    for (int i = 3; i <= N; i++){
        dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]);
        dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
    }
    cout << dp[N] << endl;
    
    return 0;
}