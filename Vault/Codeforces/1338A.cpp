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

int t;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vi a(n);
        for (int &x : a) cin >> x;
        int target = a[0];
        int maxneed = 0;
        for (int i = 1; i < n; i++){
            if (a[i] < target) {
                maxneed = max(maxneed, target - a[i]);
            }
            else {
                target = a[i];
            }
        }
        if (maxneed == 0) {
            cout << 0 << endl;
            continue;
        }
        cout << (int)log2(maxneed) + 1 << endl;

    }
    
    return 0;
}