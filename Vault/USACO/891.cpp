#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("shell.in", "r", stdin);
    freopen("shell.out", "w", stdout);

    int n;
    cin >> n;
    vector<array<int, 3>> steps;
    for (int i = 0; i < n; i++) {
        int a, b, g;
        cin >> a >> b >> g;
        steps.push_back({a, b, g});
    }

    int res = 0;

    for (int i = 1; i <= 3; i++) {
        int cur = i;
        int score = 0;
        for (auto step: steps) {
            int shell1 = step[0];
            int shell2 = step[1];
            if (cur == shell1) {
                cur = shell2;
            } else if (cur == shell2) {
                cur = shell1;
            }
            if (step[2] == cur) score++;
        }
        res = max(res, score);
    }

    cout << res << endl;
    return 0;
}