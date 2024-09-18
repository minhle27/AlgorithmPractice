#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define sz(x) int(x.size())

int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("cowqueue.in", "r", stdin);
    freopen("cowqueue.out", "w", stdout);

    cin >> n;

    vector<pi> v;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }
    sort(v.begin(), v.end());
    int res = v[0].first;
    for (auto each: v) {
        res = max(res, each.first);
        res += each.second;
    }
    cout << res << endl;
    return 0;
}