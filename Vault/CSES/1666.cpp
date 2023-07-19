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
const int maxn = 1e5 + 7;
vi g[maxn];
bool visited[maxn];
int res = 0;

void bfs(int s){
    res++;
    queue<int> q;
    visited[s] = true;
    q.push(s);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (auto v : g[u]){
            if (!visited[v]){
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g[a].PB(b);
        g[b].PB(a);
    }

    vi cities;
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= n; i++){
        if (!visited[i]) {
            cities.PB(i);
            bfs(i);
        }
    }       

    cout << res - 1 << endl;
    for (int i = 0 ; i < sz(cities) - 1; i++){
        cout << cities[i] << " " << cities[i + 1] << endl;
    }
    
    return 0;
}