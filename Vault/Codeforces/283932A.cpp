#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll w, h, n;
const ll inf = 1e16;

bool P(ll x) {
    return (x/w) * (x/h) >= n;
}

int main() {
    cin >> w >> h >> n;
    ll l = 0, r = 1;
    while(!P(r)) r*=2;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        if (P(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l << endl;
    return 0;
}