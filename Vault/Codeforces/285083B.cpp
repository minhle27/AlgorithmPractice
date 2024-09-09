#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define sz(x) int(x.size())

bool P(ll x, vi& a, int k){
    int cnt = 0;
    int sz_a = sz(a);
    ll cur = 0;
    int i = 0;
    while (i < sz_a) {
        cur += a[i];
        if (cur > x) {
            cur -= a[i];
            if (cur == 0) return false;
            cnt++;
            cur = 0;
        } else {
            i++;
            if (i == sz_a) {
                cnt++;
            }
        }
    }
    return cnt <= k;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vi a;
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        a.push_back(num);
    }

    ll lo = 0, hi = 1e14 + 3;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (P(mid, a, k)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << endl;
}