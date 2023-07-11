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

int n, res;
string s;

void solve(){
    cin >> n >> s;
    for (int i = 1; i <= n; i++){
        set<string> st;
        for (int j = 0; j < n - i + 1; j++){
            st.insert(s.substr(j, i));
        }
        if (st.size() == n - i + 1){
            res = i; 
            break;
        }
    }
    cout << res << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("whereami.in", "r", stdin);
    freopen("whereami.out", "w", stdout);

    solve();
    
    return 0;
}