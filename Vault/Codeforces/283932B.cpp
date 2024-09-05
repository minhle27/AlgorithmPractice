#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int(x.size())

int n, k;
vi ropes;

bool P(double x) {
    int cnt = 0;
    for (auto rope : ropes) {
        int pieces = floor(rope / x);
        cnt += pieces;
    }  
    return cnt < k;
}



int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int len;
        cin >> len;
        ropes.push_back(len);
    }
    double l = 0, r = 1e9 + 7;
    for (int i = 0; i < 1000; i++) {
        double mid = l + (r - l)/2;
        if (P(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(8) << l + (r - l) / 2 << endl;
    return 0;
}