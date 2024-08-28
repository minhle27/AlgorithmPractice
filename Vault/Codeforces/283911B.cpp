#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int((x).size())
vi a;

int main() {
    int n, k;
    cin >> n >> k;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        int num; 
        cin >> num;
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            if (a[mid] > num) {
                hi = mid - 1;
            } else {
                lo = mid;
            }
        }

        if (a[lo] > num) {
            cout << 0 << endl;
        }
        else {
            cout << lo << endl;
        }
    }
}