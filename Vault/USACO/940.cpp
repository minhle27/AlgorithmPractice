#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

vi reachness;
vector<vi> g;

void dfs(int u) {
    for (int next : g[u]) {
        reachness[next]++;
        dfs(next);
    }
}

int main() {
    freopen("factory.in", "r", stdin);
    freopen("factory.out", "w", stdout);

    int n;
    cin >> n;
    g = vector<vi> (n + 1);
    reachness = vi (n + 1, 0);

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; i++) {
        dfs(i);
    }
    for (int i = 1; i <= n; i++) {
        if (reachness[i] == n - 1) {
            cout << i << endl;
            return 0;
        }
    }

    cout << -1 << endl;
}
