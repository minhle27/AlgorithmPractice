#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
vi a;
int n, k;

int findClosestRight(int num) {
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= num) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    if (a[lo] < num) {
        return -1;
    } 
    return lo;
}

int findCLosestLeft(int num) {
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
        return -1;
    } 
    return lo;
}

int main() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a.begin() + 1, a.end());

    cin >> k;
    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;
        int id1 = findClosestRight(l);
        int id2 = findCLosestLeft(r);

        if (id1 == -1 || id2 == -1) {
            cout << 0 << " ";
            continue;
        }

        if (a[id1] < l) {
            cout << 0 << " ";
        }
        else {
            cout << id2 - id1 + 1 << " ";
        }
    }
}