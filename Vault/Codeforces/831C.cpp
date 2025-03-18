#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define DEBUG(x) { cout << #x << " = " << (x) << endl; }

int main() {
    int k, n;
    cin >> k >> n;
    vi a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    vi b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    set<int> s;
    s.insert(a[0]);
    int cur = a[0];
    vi pref;
    pref.push_back(cur);
    for (int i = 1; i < k; i++) {
        cur += a[i];
        s.insert(cur);
        pref.push_back(cur);
    }

    int res = 0;
    set<int> pos;
    for (int i = 0; i < k; i++) {
        int x = b[0] - pref[i];
        if (pos.count(x) != 0) continue;
        map<int, bool> isFree;
        for (int j = 0; j < k; j++)
            isFree[pref[j]] = true;
        bool flag = true;
        for (int j = 1; j < n; j++) {
            if (!s.count(b[j] - x) || !isFree[b[j] - x]) {
                flag = false;
                break;
            } else {
                isFree[b[j] - x] = false;
            }
        }
        if (flag) {
            res++;
            pos.insert(x);
        }
    }
    cout << res << endl;
}
