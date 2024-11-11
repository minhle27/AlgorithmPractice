#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;


vector<bool> visited;

void dfs(int s, const vector<vi>& g) {
    visited[s] = true;
    for (auto u: g[s]) {
        if (!visited[u]) {
            dfs(u, g);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vi> g = vector<vi> (n + 1);
    vector<vi> rev_g = vector<vi> (n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rev_g[b].push_back(a);
    }
    visited = vector<bool> (n + 1, false);

    dfs(1, g);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "NO" << endl;
            cout << 1 << " " << i << endl;
            return 0;
        }
    }

    visited = vector<bool> (n + 1, false);
    dfs(1, rev_g);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "NO" << endl;
            cout << i << " " << 1 << endl;
            return 0;
        }
    }

    cout << "YES" << endl;


}
