#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using pi = pair<int, int>;
#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }

ll n, k;

ll calc(ll x, vector<pll>& v){
    ll cnt = 0;
    for (auto cur : v) {
        ll l = cur.first;
        ll r = cur.second;
        if (x <= l) {
            continue;
        } else {
            cnt += min(x - l, r - l + 1);
        }
    }
    return cnt;
}

int main() {
    cin >> n >> k;
    vector<pll> v;
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }

    ll lo = -2e9 - 7, hi = 2e9 + 7;
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;
        if (calc(mid, v) <= k) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo << endl;

    return 0;
}