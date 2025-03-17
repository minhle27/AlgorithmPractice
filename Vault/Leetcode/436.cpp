#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int((x).size())

class Solution {
public:
    int search(const vi &cur, const vector<vi>& intervals) {
        int lo = 0, hi = sz(intervals) - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (intervals[mid][0] >= cur[1]) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        if (intervals[lo][0] >= cur[1]) {
            return intervals[lo][2];
        } else {
            return -1;
        }
    }

    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        for (int i = 0; i < sz(intervals); i++) {
            intervals[i].push_back(i);
        } 
        vi res(sz(intervals));
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < sz(intervals); i++) {
            res[intervals[i][2]] = search(intervals[i], intervals);
        }
        return res;
    }
};
