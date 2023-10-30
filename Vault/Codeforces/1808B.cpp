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

int n, m;

ll f (vl col){
    ll res = 0;
    for (int i = 0; i < n; i++){
        res += col[i] * (2 * i - n + 1);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;

    while (t--) {
        cin >> n >> m;
        vector<vl> card(n, vl(m));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> card[i][j];
            }
        }
        ll ans = 0;
        for (int j = 0; j < m; j++){
            vl col;
            for (int i = 0; i < n; i++){
                col.PB(card[i][j]);
            }
            sort(col.begin(), col.end());
            ans += f(col);
        }
        cout << ans << endl;
    }
    
    return 0;
}