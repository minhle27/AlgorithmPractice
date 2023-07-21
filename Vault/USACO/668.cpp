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

int N;
const int maxn = 205;
vector<pair<pi, int>> points;
vector<bool> visited(maxn, false);

double dis(pi p1, pi p2){
    return sqrt(pow(p1.first - p2.first, 2) +
                pow(p1.second - p2.second, 2));
}

int bfs(int s){
    visited[s] = true;
    queue<int> q;
    q.push(s);
    int res = 1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for (int i = 0; i < N; i++){
            double dist = dis(points[u].f, points[i].f);
            if (0 < dist && dist <= points[u].s && !visited[i]){
                q.push(i);
                visited[i] = true;
                res++;
            }
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    cin >> N; 
    
    for (int i = 0; i < N; i++){
        int x, y, p;
        cin >> x >> y >> p;
        points.PB({{x, y}, p});
    }

    int res = 0;
    for (int i = 0; i < N; i++){
        res = max(res, bfs(i));
        visited = vector<bool> (maxn, false);
    }

    cout << res << endl;

    return 0;
}