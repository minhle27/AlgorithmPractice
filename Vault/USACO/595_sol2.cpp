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

const int maxn = 50005;
const int INF = 1e9 + 7;
int n, num;
int first[7], last[7];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);
    
    cin >> n;
    memset(first, INF, sizeof(first));
    int curPref = 0;
    for (int i = 1; i <= n; i++){
        cin >> num;
        curPref += num;
        curPref %= 7;
        first[curPref] = min(first[curPref], i);
        last[curPref] = i;
    }

    int res = 0;
    for (int i = 0; i < 7; i++){
        if (first[i] <= n){
            res = max(res, last[i] - first[i]);
        }
    }

    cout << res << endl;

    return 0;
}