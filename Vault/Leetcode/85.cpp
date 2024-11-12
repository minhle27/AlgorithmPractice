#include <bits/stdc++.h>
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
    int maxArea(const vi& a) {
        int res = 0;

        map<int, int> left;
        map<int, int> right;

        stack<int> st;
        for (int i = 0; i < sz(a); i++) {
            while (!st.empty() && a[st.top()] >= a[i]) {
                st.pop();
            }
            left[i] = -1;
            if (!st.empty()) left[i] = st.top();
            st.push(i);
        }

        stack<int> st_right;
        for (int i = sz(a) - 1; i >= 0; i--) {
            while (!st_right.empty() && a[st_right.top()] >= a[i]) {
                st_right.pop();
            }
            right[i] = sz(a);
            if (!st_right.empty()) right[i] = st_right.top();
            st_right.push(i);
        }

        for (int i = 0 ; i < sz(a); i++) {
            int left_id = left[i];
            int right_id = right[i];
            ckmax(res, (a[i]) * (right_id - left_id - 1));
        }

        return res;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int res = -1;
        int m = sz(matrix);
        int n = sz(matrix[0]);
        vi height(n, 0);
        for (int k = 0; k < m; k++) {
            for (int j = 0; j < n; j++) {
                if (matrix[k][j] == '0') {
                    height[j] = 0;
                } else {
                    height[j]++;
                }
            }
            ckmax(res, maxArea(height));
        }
        return res;
    }
};
