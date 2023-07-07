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

const ll MAX = 1e5 + 7;
const ll INF = 1e9 * 2 + 5;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> b(n), c(n);

    for (int i = 0; i < n; i++){
        cin >> b[i];
    }

    for (int i = 0; i < n; i++){
        cin >> c[i];
    }

    sort(b.begin(), b.end()); sort(c.begin(), c.end());

    ll ans = INF; int i = 0; int j = n - 1;
    while (i <= n - 1 && j >= 0) {
        ans = min(ans, abs(b[i] + c[j]));
        if (b[i] + c[j] > 0) j--;
        else if (b[i] + c[j] == 0) break;
        else i++;
    }
    
    cout << ans << endl;
    return 0;
}