#include <bits/stdc++.h>
using namespace std;

#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
using vi = vector<int>;
using pi = pair<int, int>;

int n;

void toggle(vector<vi>& cows, int row, int col) {
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            cows[i][j] = 1 - cows[i][j];
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("cowtip.in", "r", stdin);
    freopen("cowtip.out", "w", stdout);

    cin >> n;

    vector<vi> cows(n, vi(n));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            cows[i][j] = s[j] - '0';
        }
    }

    int row = n - 1;
    int col = n - 1;
    int res = 0;


    while (row >= 0 && col >= 0) {
        if (cows[row][col] == 1) {
            res++;
            toggle(cows, row, col);
        }
        if (col > 0) col--;
        else {
            row--;
            col = n - 1;
        }
    }

    cout << res << endl;
    return 0;
}
