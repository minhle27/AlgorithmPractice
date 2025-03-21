#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vi a(n + 1);
        vi b(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
        }
        int res = 0;
        int cursum = 0;
        int curmax = -1;
        for (int i = 1; i <= min(n, k); i++) {
            cursum += a[i];
            curmax = max(curmax, b[i]);
            res = max(res, cursum + curmax * (k - i));
        }
        cout << res << endl;
    }
}
