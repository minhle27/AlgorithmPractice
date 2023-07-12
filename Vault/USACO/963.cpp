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

int n, k;
const int maxn = 25;
int cows[maxn][maxn];
int ranks[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);

    cin >> k >> n;

    for (int i = 1; i <= k; i++){
        for (int j = 1; j <= n; j++){
            int cow; cin >> cow;
            cows[i][j] = cow;
            ranks[i][cow] = j;
        }
    }

    vector<pi> potential;
    for (int j = 1; j <= n; j++){
        for (int t = j + 1; t <= n; t++){
            potential.PB({cows[1][j], cows[1][t]});
        }
    }

    int res = potential.size();

    for (auto each: potential){
        for (int i = 2; i <= k; i++){
            if (ranks[i][each.f] > ranks[i][each.s]){
                res--;
                break;
            }
        }
    }

    cout << res << endl;
    
    return 0;
}