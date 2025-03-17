#include <bits/stdc++.h>
using namespace std;

using pi = pair<int, int>;
using vi = vector<int>;

#define DEBUG(x) { cout << #x << " = " << (x) << endl; }

int main() {
    freopen("speeding.in", "r", stdin);
    freopen("speeding.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    vi legal(100);  
    int prev = 0;
    for (int i = 0; i < n; i++) {
        int len, speed;
        cin >> len >> speed;
        for (int j = prev; j < prev + len; j++) legal[j] = speed;
        prev += len;
    }

    vi own(100);
    prev = 0;
    for (int i = 0; i < m; i++) {
        int len, speed;
        cin >> len >> speed;
        for (int j = prev; j < prev + len; j++) own[j] = speed;
        prev += len;
    }


    int res = 0;

    for (int i = 0; i < 100; i++) {
        res = max(res, own[i] - legal[i]);
    }
    cout << res << endl;
}
