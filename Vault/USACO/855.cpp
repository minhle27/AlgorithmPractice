#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pi = pair<int, int>;
#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("mixmilk.in", "r", stdin);
    freopen("mixmilk.out", "w", stdout);

    vector<pi> v;
    for (int i = 0; i < 3; i++) {
        int c, m;
        cin >> c >> m;
        v.push_back({c, m});
    }

    int cur = 0, next = 1;
    for (int i = 0; i < 100; i++) {
        int m_cur = v[cur].second;
        int m_next = v[next].second;
        int c_next = v[next].first;

        if (m_cur + m_next <= c_next) {
            v[cur].second = 0;
            v[next].second += m_cur;
        } else {
            int change = c_next - m_next;
            v[next].second = c_next;
            v[cur].second -= change;
        }
        cur = next;
        next = (next + 1) % 3;
    }
    for (auto each : v) {
        cout << each.second << endl;
    }
    return 0;
}