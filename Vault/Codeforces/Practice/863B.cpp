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

const int maxn = 55;
const int INF = 1e9 + 7;
int n; 
int res;
bool mark[2 * maxn];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vi w(2 * n);
    for (int i = 0; i < 2 * n; i++){
        cin >> w[i];
    }

    sort(w.begin(), w.end());
    memset(mark, false, sizeof(mark));

    int i = 0; res = INF;
    for (int i = 0; i < 2 * n; i++){
        for (int j = 0; j < 2 * n; j++){
            if (i == j) continue;
            int cur = 0;
            mark[i] = mark[j] = true;

            vi new_w(2 * n - 2);
            int l = 0;
            for (int k = 0; k < 2 * n; k++){
                if (mark[k]) continue;
                new_w[l] = w[k]; l++;
            }

            int k = 0;
            while (k < 2 * n - 3){
                cur += abs(new_w[k] - new_w[k + 1]);
                k += 2;
            }
            
            res = min(res, cur);
            mark[i] = mark[j] = false;
        }
    }
    cout << res << endl;
    
    return 0;
}