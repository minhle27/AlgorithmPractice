#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector<vector<char>> v(2 * n, vector<char> (m));
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }
    int res = 0;
    for (int j = 0; j < m; j++) {
        map<char, int> m;
        for (int i = 0; i < n; i++) {
            m[v[i][j]]++;
        }
        bool flag = false;
        for (int i = n; i < 2*n; i++) {
            if (m[v[i][j]] != 0) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            res++;
        }
    }
    cout << res << endl;
    return 0;
}