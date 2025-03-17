#include <bits/stdc++.h>
using namespace std;

using pi = pair<int, int>;
using vi = vector<int>;

#define sz(x) int((x).size())
#define DEBUG(x) { cout << #x << " = " << (x) << endl; }

int main() {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    string s;
    cin >> s;


    vector<vi> v(26);
    for (int i = 0; i < sz(s); i++) {
        v[s[i] - 'A'].push_back(i);
    }

    int res = 0;
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (v[i][0] < v[j][0] && v[j][0] < v[i][1] && v[i][1] < v[j][1] ||
                v[j][0] < v[i][0] && v[i][0] < v[j][1] && v[j][1] < v[i][1]) {
                res++;
            }
        }
    }
    cout << res << endl;
}
