#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }

int main() {
    int n;
    cin >> n;
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    sort(c.begin(), c.end());
    ll res = -1;
    int charge = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] * (n - i) > res) {
            res = c[i] * (n - i);
            charge = c[i];
        }
    }
    cout << res << " " << charge << endl;
    return 0;
}