#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pi = pair<int, int>;
#define sz(x) int(x.size())

const int inf = 1e9 + 7;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        intervals.push_back({inf, -1});

        int l = intervals[0][0];
        int r = intervals[0][1];

        vector<vi> res;

        int m = sz(intervals);
        for (int i = 1; i < m; i++) {
            if (intervals[i][0] <= r) {
                r = max(r, intervals[i][1]);
            } else {
                res.push_back({l, r});
                l = intervals[i][0];
                r = intervals[i][1];
            }
        }
        return res;
    }
};