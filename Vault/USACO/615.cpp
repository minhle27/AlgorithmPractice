#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);
    int x, y, m;
    cin >> x >> y >> m;
    int res = 0;
    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            if (i * x + j * y <= m) {
                res = max(res, i * x + j * y);
            }
        }
    } 
    cout << res << endl;
}
