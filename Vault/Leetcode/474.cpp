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
    int memo[605][105][105];
    int size;
public:
    int dp(int id, int rem_m, int rem_n, const vector<string>& strs) {
        if ((id == size) || (rem_m == 0 && rem_n == 0)) return 0;
        int &ans = memo[id][rem_m][rem_n];
        if (ans != -1) return ans;
        string cur = strs[id];
        int cnt1 = count1(cur);
        int cnt0 = sz(cur) - cnt1;
        DEBUG(cnt1); DEBUG(cnt0); DEBUG(cur);
        if (cnt1 > rem_n || cnt0 > rem_m) return ans = dp(id + 1, rem_m, rem_n, strs);
        return ans = max(dp(id + 1, rem_m, rem_n, strs),
                        1 + dp(id + 1, rem_m - cnt0, rem_n - cnt1, strs));
    }

    int count1(string s) {
        int res = 0;
        for (int i = 0; i < sz(s); i++) {
            if (s[i] == '1') res++;
        }
        return res;
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        size = sz(strs);
        memset(memo, -1, sizeof memo);
        return dp(0, m, n, strs);
    }   
};