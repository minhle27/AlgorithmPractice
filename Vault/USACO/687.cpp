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

int n, amount, M; string cow;
const int INF = 1e9 + 7;

void solve(){
    cin >> n;
    map<string, int> m;
    
    for (int i = 0; i < n; i++){
        cin >> cow >> amount;
        m[cow] += amount;
    }

    bool flag = false;

    // find smallest and second smallest in the list
    pair<string, int> smallest = {"", INF}; 
    for (const auto &it: m){
        if (it.second < smallest.second){
            flag = false;
            smallest = it;
        }
        else if (it.second == smallest.second){
            flag = true;
        }
    }

    if (m.size() != 7) {
        if (flag) cout << "Tie" << endl;
        else cout << smallest.first << endl;
    }
    else {
        pair<string, int> smallest_2nd = {"", INF};
        flag = false;
        for (const auto &it: m){
            if (it.second < smallest_2nd.second && it.second > smallest.second){
                flag = false;
                smallest_2nd = it;
            }
            else if (it.second == smallest_2nd.second){
                flag = true;
            }
        } 
        if (flag || smallest_2nd.second == INF) cout << "Tie" << endl;
        else cout << smallest_2nd.first << endl;
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("notlast.in", "r", stdin);
    freopen("notlast.out", "w", stdout);

    solve();

    return 0;
}