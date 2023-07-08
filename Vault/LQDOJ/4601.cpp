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

int n, m;
const int MAX = 1e5 + 7;
vector<int> g[MAX];
bool visited[MAX];
int components = 0;

void bfs(int s){
    components++;
    visited[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (auto v: g[u]){
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
    while (m--){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }    
    fill_n(visited, n + 1, false);

    for (int i = 1; i <= n; i++){
        if (!visited[i]) bfs(i);
    }

    cout << components << endl;
    
    return 0;
}