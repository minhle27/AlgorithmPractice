#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vll = vector<ll>;

#define sz(x) int((x).size())
#define DEBUG(x)                                                               \
    {                                                                          \
        cout << #x << " = " << (x) << endl;                                    \
    }

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        map<int, vi> m;
        vi a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            m[a[i] - i].push_back(a[i]);
        }
        ll res = 0;
        for (const auto &comp : m) {
            vi lst = comp.second;
            sort(lst.begin(), lst.end());
            for (int i = sz(lst) - 1; i >= 1; i -= 2) {
                if (lst[i] + lst[i - 1] >= 0) {
                    res += (ll) lst[i] + (ll) lst[i - 1];
                } else {
                    break;
                }
            } 
        }
        cout << res << endl;
    }
}
