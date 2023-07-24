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
const int INF = 1e9 + 7;
vector<pi> cows;
vector<vi> g;
vector<bool> visited;

int bfs(int s){
    queue<int> q;
    visited[s] = true;
    q.push(s);
    int min_y, max_y, min_x, max_x;
    max_y = min_y = cows[s].second;
    max_x = min_x = cows[s].first;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : g[u]){
            if (!visited[v]){
                visited[v] = true;
                q.push(v);
                max_y = max(max_y, cows[v].second);
                min_y = min(min_y, cows[v].second);
                max_x = max(max_x, cows[v].first);
                min_x = min(min_x, cows[v].first);
            }
        }
    }
    return 2 * ((max_y - min_y) + (max_x - min_x));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);

    cin >> n >> m;
    g = vector<vi>(n + 1);
    visited = vector<bool>(n + 1, false);
    cows.resize(n + 1);

    for (int i = 1; i <= n; i++){
        int a, b;
        cin >> a >> b;
        cows[i] = {a, b};
    }

    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g[a].PB(b); 
        g[b].PB(a);
    }
    
    int res = INF;
    for (int i = 1; i <= n; i++){
        if (!visited[i]) res = min(res, bfs(i));
    }
    cout << res << endl;

    
    return 0;
}