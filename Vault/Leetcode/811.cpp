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
    pair<int, vector<string>> extract(const string& cpdomain) {
        vector<string> res;
        stringstream ss(cpdomain);
        int count; string domain;
        ss >> count >> domain;
        ss.str("");
        ss.clear();
        ss << domain;
        string token;
        while (getline(ss, token, '.')) {
            res.push_back(token);
        }
        vector<string> subdomains;
        if (sz(res) == 3) {
            subdomains = {res[1] + '.' + res[2], res[2], res[0] + '.' + res[1] + '.' + res[2]};
        } else {
            subdomains = {res[1], res[0] + '.' + res[1]};
        }
        return {count, subdomains};
    }

    vector<string> subdomainVisits(vector<string>& cpdomains) {
        vector<string> res;
        map<string, int> m;

        for (auto& cpdomain: cpdomains) {
            auto [count, subdomains] = extract(cpdomain);  
            for (const auto& subdomain: subdomains) {
                m[subdomain] += count;
            }
        }
        for (const auto& entry: m) {
            int cnt = entry.second;
            string name = entry.first;
            stringstream ss {};
            ss << cnt << ' ' << name;
            res.push_back(ss.str());
        }
        return res;
    }
};
