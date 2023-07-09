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
const int MAX = 705;
int a[MAX][MAX];
bool visited[MAX][MAX];
int res = 0; bool flag;

int dx[] = {0, 0, 1, -1, -1, -1, 1, 1};
int dy[] = {1, -1, 0, 0, -1, 1, -1, 1};

bool isValid(int r, int c){
    return r >= 0 && r < n && c >= 0 && c < m;
}

bool notMount(int r, int c){
    bool check = false;
    for (int i = 0; i < 8; i++){
        int x = r + dx[i];
        int y = c + dy[i];
        if (isValid(x, y) && a[x][y] > a[r][c]){
            check = true; break;
        }
    }
    return check;
};

void bfs(pi c){
    queue<pi> q;
    q.push(c);
    visited[c.f][c.s] = true;

    while (!q.empty()){
        int x = q.front().f;
        int y = q.front().s;
        if (notMount(x, y)) flag = false;
        q.pop();
        for (int i = 0; i < 8; i++){
            int u = x + dx[i];
            int v = y + dy[i];
            if (isValid(u, v) && !visited[u][v] && a[x][y] == a[u][v]){
                q.push({u, v});
                visited[u][v] = true;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (!visited[i][j]){
                flag = true;
                bfs({i, j});
                if (flag) res++;
            }
        }
    }
    
    cout << res << endl;
    
    return 0;
}