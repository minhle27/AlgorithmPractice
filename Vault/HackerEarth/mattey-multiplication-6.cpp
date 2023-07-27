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

ll t, n, m;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n >> m; 
        ll id = 0;
        vl p;
        while (m > 0){
            if((m & 1) == 1) {
                p.PB(id);
            }
            m >>= 1;
            id++;
        }
        for (auto it = p.rbegin(); it != p.rend(); it++){
            cout << "(" << n << "<<" << *it << ") ";
            if (it != p.rend() - 1){
                cout << "+ ";
            }
        }
        cout << endl;
    }
    
    return 0;
}