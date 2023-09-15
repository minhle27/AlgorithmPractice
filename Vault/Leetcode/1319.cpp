#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef tuple<int, int, int> iii;

#define PB push_back
#define MP make_pair

#define LSOne(S) ((S) & -(S))
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define tcT template<class T

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

// const int MOD = (int)1e9+7;
// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>; // minheap

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

// bitwise ops
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0); 
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

class Solution {
    vector<bool> visited;
    vector<vi> g;
public:
    void dfs(int s) {
        visited[s] = true;
        for (auto u : g[s]) {
            if (!visited[u]) dfs(u);
        }
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        int m = (int)connections.size();
        if (m < n - 1) return -1;

        g = vector<vi> (n + 7);
        visited = vector<bool> (n + 7, false);

        for (auto edge : connections) {
            int u = edge[0], v = edge[1];
            g[u].PB(v);
            g[v].PB(u);
        }

        int comps = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i); comps++;
            }
        }

        return comps - 1;

    }
};