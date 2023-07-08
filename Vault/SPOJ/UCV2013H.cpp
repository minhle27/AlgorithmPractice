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

const int MAX = 300;
bool a[MAX][MAX], visited[MAX][MAX];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
vi slicks;

void reset() {
    slicks.clear();
    memset(visited, false, sizeof(visited));
}

bool isValid(int r, int c){
    return r >= 0 && r < n && c >= 0 && c < m;
}

int bfs(pi c){
    int size = 1;
    visited[c.f][c.s] = true;
    queue<pi> q;
    q.push(c);
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++){
            int u = x + dx[i];
            int v = y + dy[i];
            if (isValid(u, v) && a[u][v] == 1 && !visited[u][v]){
                q.push({u, v});
                size++;
                visited[u][v] = true;
            }
        }
    }
    return size;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> a[i][j];
            }
        }

        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (a[i][j] == 1 && !visited[i][j]){
                    slicks.push_back(bfs({i, j}));
                }
            }
        }

        cout << slicks.size() << endl;

        sort(slicks.begin(), slicks.end());
        slicks.push_back(1e9);
        int cnt = 0, prev = slicks[0];
        for (int i = 0; i < slicks.size(); i++){
            if (slicks[i] != prev){
                cout << prev << " " << cnt << endl;
                cnt = 1;
                prev = slicks[i];
            }
            else{
                cnt++;
            }
        }
        reset();
    }
    return 0;
}