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
bool visited[9];
map<string, int> cows_ind;
vector<string> COWS;
vector<vi> graph(8);

void dfs(int s){
    if (visited[s]) return;
    visited[s] = true;
    cout << COWS[s] << endl;
    for (auto u : graph[s]){
        dfs(u);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
    
    COWS = {"Bessie", "Buttercup", "Belinda", "Beatrice", "Bella",  "Blue", "Betsy", "Sue"};
    sort(COWS.begin(), COWS.end());

    for (int i = 0; i < sz(COWS); i++){
        cows_ind[COWS[i]] = i;
    }

    cin >> n;

    for (int i = 0; i < n; i++){
        string cow1, cow2, trash;
        cin >> cow1 >> trash >> trash >> trash >> trash >> cow2;
        int c1 = cows_ind[cow1];
        int c2 = cows_ind[cow2];
        graph[c1].PB(c2);
        graph[c2].PB(c1);
    }

    memset(visited, false, sizeof(visited));
    for (int i = 0; i < 8; i++){
        if (!visited[i] && graph[i].size() <= 1) dfs(i);
    }
    
    return 0;
}