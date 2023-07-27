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

string s; int n;
map<char, int> m;
string cur;
vector<string> res;

void backtrack(int i) {
    if (i == n) {
        res.PB(cur);
    }
    else {
        for (auto each : m){
            if (each.second > 0){
                cur += each.first;
                m[each.first]--;
                backtrack(i + 1);
                m[each.first]++;
                cur = cur.substr(0, sz(cur) - 1);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s; n = sz(s);
    for (int i = 0; i < n; i++){
        m[s[i]]++;
    }

    backtrack(0);

    cout << sz(res) << endl;
    for (auto ans : res) {
        cout << ans << endl;
    }
    
    return 0;
}