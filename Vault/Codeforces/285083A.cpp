#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pi = pair<int, int>;
using ll = long long;
#define sz(x) int(x.size())

bool P(double time, vector<pi>& v) {
    double max_left = -1e12;
    double min_right = 1e12;
    for (auto cur: v) {
        int spe = cur.second;
        int loc = cur.first;
        double cur_right = loc + time * spe;
        double cur_left = loc - time * spe;
        max_left = max(max_left, cur_left);
        min_right = min(min_right, cur_right);
    }
    return min_right >= max_left;
}

int main() {
    int n;
    cin >> n;
    vector<pi> v;
    for (int i = 0; i < n; i++) {
        int loc, spe;
        cin >> loc >> spe;
        v.push_back({loc, spe});
    }

    double lo = 0, hi = 1e12 + 7;
    for (int i = 0; i < 100; i++) {
        double mid = lo + (hi - lo) / 2;
        if (P(mid, v)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(8) << lo + (hi - lo) / 2 << endl;
}