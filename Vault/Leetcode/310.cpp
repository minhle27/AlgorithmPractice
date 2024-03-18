#include <bits/stdc++.h>
#include <queue>
using namespace std;

using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using vi = vector<int>;
using vl = vector<ll>;
using iii = tuple<int, int, int>;

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

tcT> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
tcT> T lcm(T a, T b) { return a / gcd(a, b) * b; }

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

// bitwise ops
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0);
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x))
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

class Solution {

public:
    pi dfs(int cur, int par, vector<vi>& g) {
        pi res = {0, cur};
        for (auto u : g[cur]) {
            if (u == par) continue;
            pi tmp = dfs(u, cur, g);
            tmp.first++;
            ckmax(res, tmp);
        }
        return res;
    }

    void dfs2(int cur, int par, vector<vi>& g, vi& d1) {
        for (auto u : g[cur]) {
            if (u == par) continue;
            d1[u] = d1[cur] + 1;
            dfs2(u, cur, g, d1);
        }
    }

    void dfs3(int cur, int par, vector<vi>& g, vi& d2) {
        for (auto u : g[cur]) {
            if (u == par) continue;
            d2[u] = d2[cur] + 1;
            dfs3(u, cur, g, d2);
        }
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vi res;
        vector<vi> g(n);
        vi d1(n + 7, 0), d2(n + 7, 0);
        if (sz(edges) == 0) {
            res.push_back(0);
            return res;
        }
        for (auto each : edges) {
            g[each[0]].push_back(each[1]);
            g[each[1]].push_back(each[0]);
        }
        int end1 = dfs(0, -1, g).second;
        int end2 = dfs(end1, -1, g).second;
        dfs2(end1, -1, g, d1);
        dfs3(end2, -1, g, d2);

        int min_h = 1e9;
        for (int i = 0; i < n; i++) {
            int cur_h = max(d1[i], d2[i]);
            ckmin(min_h, cur_h);
        }

        for (int i = 0; i < n; i++) {
            int cur_h = max(d1[i], d2[i]);
            if (cur_h == min_h) {
                res.push_back(i);
            }
        }
        return res;
    }
};
