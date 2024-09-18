#include <bits/stdc++.h>
using namespace std;

#define sz(x) int(x.size())
using vi = vector<int>;
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }

int n, t;
vector<vi> stc;
vector<vi> abpm;

void solve(int i, vi& subset, int& res) {
    if (i == t) {
        vi check(101);
        int cost = 0;

        for (auto each: subset) {
            vi ac = abpm[each];
            int a = ac[0];
            int b = ac[1];
            int p = ac[2];
            int m = ac[3];
            for (int i = a; i <= b; i++) {
                check[i] += p;
            }
            cost += m;
        }

        bool flag = true;
        for (auto cur: stc){
            int s = cur[0];
            int t = cur[1];
            int c = cur[2];
            for (int i = s; i <= t; i++) {
                if (check[i] < c) {
                    flag = false;
                }
            }
        }
        if (flag) {
            res = min(res, cost);
        }
    } 
    else {
        solve(i + 1, subset, res);
        subset.push_back(i);
        solve(i + 1, subset, res);
        subset.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> t;
    stc.resize(n + 1, vi(3));
    for (int i = 0; i < n; i++) {
        cin >> stc[i][0] >> stc[i][1] >> stc[i][2];
    }
    abpm.resize(t + 1, vi(4));
    for (int i = 0; i < t; i++) {
        cin >> abpm[i][0] >> abpm[i][1] >> abpm[i][2] >> abpm[i][3];
    }
    vi subset;
    
    int res = 1e9;
    solve(0, subset, res);
    cout << res << endl;
    return 0;
}