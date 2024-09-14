#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vb = vector<bool>;
#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }

class Solution {
    vector<vector<string>> res;
public:
    void attempt(int i, int n, vb& a, vb& diag_TLBR, vb& diag_TRBL, vi& v) {
        for (int j = 1; j <= n; j++) {
            if (a[j] && diag_TLBR[i - j + n - 1] && diag_TRBL[i + j]) {
                v[i] = j;
                if (i == n) {
                    vector<string> cur;
                    for (int r = 1; r <= n; r++) {
                        string row = "";
                        for (int t = 0; t < v[r] - 1; t++) {
                            row += '.';
                        }
                        row += 'Q';
                        for (int t = v[r]; t < n; t++) {
                            row += '.';
                        }
                        cur.push_back(row);
                    }
                    res.push_back(cur);
                } else {
                    a[j] = false; diag_TLBR[i - j + n - 1] = false; diag_TRBL[i + j] = false;
                    attempt(i + 1, n, a, diag_TLBR, diag_TRBL, v);
                    a[j] = true; diag_TLBR[i - j + n - 1] = true; diag_TRBL[i + j] = true;
                }
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vb a (n + 1, true);
        vb diag_TLBR (2 * n, true);
        vb diag_TRBL (2 * n, true);
        vi v (n + 1, 0);
        attempt(1, n, a, diag_TLBR, diag_TRBL, v);
        return res;
    }
};