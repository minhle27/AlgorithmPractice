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

int n; 
string A, B;
bool flag;

void solve(){
    cin >> n;
    cin >> A >> B;
    flag = false;
    int ans = 0;
    for (int i = 0; i < n; i++){
        if (A[i] != B[i]){
            flag = true;
        }
        else {
            if (flag){
                ans++; flag = false;
            }
        }
    }
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("breedflip.in", "r", stdin);
    freopen("breedflip.out", "w", stdout);

    solve();
    
    return 0;
}