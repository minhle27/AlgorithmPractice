#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int((x).size())

class Solution {
public:
    vector<vi> res;

    void choose(vi& cur, int x, const vi& nums) {
        if (x == sz(nums)) {
            res.push_back(cur);
        } else {
            cur.push_back(nums[x]);
            choose(cur, x + 1, nums);
            cur.pop_back();
            choose(cur, x + 1, nums);
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vi cur;
        choose(cur, 0, nums);
        return res;
    }
};
