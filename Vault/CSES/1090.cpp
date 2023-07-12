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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x; cin >> n >> x;
    vi a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    
    int i = 0, j = n - 1, res = 0;
    while (i < j){
        if (a[i] + a[j] <= x){
            res++; i++; j--;
        }
        else {
            res++; j--;
        }
    }
    if (i == j) res++;

    cout << res << endl;
    
    return 0;
}
