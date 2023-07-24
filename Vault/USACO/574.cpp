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

int t, x, y;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    cin >> t >> x >> y;
    vector<vector<bool>> seen(2, vector<bool>(t + 1, false));
    seen[0][0] = true;
    for (int a = 0; a < 2; a++){
        for (int i = 0; i <= t; i++){
            if (!seen[a][i]) continue;
            if (i + x <= t) seen[a][i + x] = true;
            if (i + y <= t) seen[a][i + y] = true;
            if (a + 1 < 2) seen[a + 1][i / 2] = true;
        }
    }

    int ret = t;
    while (!seen[1][ret]) ret--;

    cout << ret << endl;
    return 0;
}