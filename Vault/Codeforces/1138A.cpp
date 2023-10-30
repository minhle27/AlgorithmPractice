#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
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

const int N = 1e5 + 9;
int n;
int a[N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    a[n + 1] = -1;
    
    int ans(0); int cnt(0); int cntprev(0);

    for (int i = 1; i <= n + 1; i++){
        if (a[i] != a[i - 1]) {
            ans = max(ans, min(cntprev, cnt) * 2);
            cntprev = cnt;
            cnt = 1;
        }
        else {
            cnt++;
        }
    }

    cout << ans << endl;
    return 0;
}