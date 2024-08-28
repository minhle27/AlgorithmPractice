#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

int main() {
    int n, k;
    cin >> n >> k;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= k; i++) {
        int num;
        cin >> num;
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] >= num) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        if (a[lo] >= num) {
            cout << lo << endl;
        } else {
            cout << n + 1 << endl;
        }
    }
    return 0;
}