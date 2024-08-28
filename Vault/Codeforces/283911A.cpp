#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int((x).size())

bool isInList(int num, vi& a) {
    int size = sz(a);
    int lo = 1, hi = size;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == num) return true;
        else if (a[mid] < num) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        int num;
        cin >> num;
        if (isInList(num, a)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}