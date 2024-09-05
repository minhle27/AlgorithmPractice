#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pi = pair<int, int>;
#define sz(x) int(x.size())

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int m = sz(intervals);
        vector<pi> a;
        for (int i = 0; i < m; i++) {
            a.push_back({intervals[i][0], 1});
            a.push_back({intervals[i][1], -1});
        }
        sort(a.begin(), a.end());

        int cur = 0;
        int res = 0;
        for (auto each: a) {
            cur += each.second;
            res = max(res, cur);
        }
        return res;
    }
};
