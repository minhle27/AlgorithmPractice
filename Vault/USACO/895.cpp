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

int n;
const int maxn = 1007;
string m[maxn];
bool visited[maxn][maxn];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool isValid(int r, int c){
    return r >= 0 && r < n && c >= 0 && c < n;
}

pi dfs(pi s){
    int i = s.f, j = s.s;
    if (visited[i][j]) return {0, 0};
    visited[i][j] = true;
    int p = 4, area = 1;
    for (int t = 0; t < 4; t++){
        int u = i + dx[t];
        int v = j + dy[t];
        if (isValid(u, v) && m[u][v] == '#') p--;
    }
    for (int t = 0; t < 4; t++){
        int u = i + dx[t];
        int v = j + dy[t];
        if (isValid(u, v) && m[u][v] == '#' && !visited[u][v]) {
            pi cur = dfs({u, v});
            p += cur.f;
            area += cur.s;
        }
    }
    return {p, area};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> m[i];
    }

    vector<pi> components;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (m[i][j] == '#' && !visited[i][j]){
                components.PB(dfs({i, j}));
            }
        }
    }

    pi res = {-1, -1};

    for (const auto &each : components) {
        if (each.s > res.s) {
            res = each;
        }
        else if (each.s == res.s && each.f < res.f) {
            res = each;
        }
    }
    
    cout << res.s << " " << res.f << endl;

    return 0;
}