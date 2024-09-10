#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pi = pair<int, int>;
#define sz(x) int(x.size())

int n, d;

vi buildPref(vi& a) {
    vi pref(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }
    return pref;
}

pi P(double x, vi& pref) {
    double curmin = 1e9;
    int l = -1;
    for (int r = d; r <= n; r++) {
        double next = pref[r - d] - x * (r - d);
        if (curmin > next) {
            curmin = next;
            l = r - d;
        }
        if (pref[r] - r*x >= curmin) return {l + 1, r};
    }
    return {-1, -1};
}

int main() {
    cin >> n >> d;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vi pref_a = buildPref(a);

    double lo = 0, hi = 1e7 + 8;
    pi res;
    for (int i = 0; i < 100; i++) {
        double mid = lo + (hi - lo) / 2;
        pi test = P(mid, pref_a);
        if (test.first != -1) {
            lo = mid;
            res = test;
        } else {
            hi = mid;
        }
    }
    if (res.first == 0 && res.second == 0) {
        res.first = 1; res.second = n;
    }
    cout << res.first << " " << res.second << endl;

    return 0;
}