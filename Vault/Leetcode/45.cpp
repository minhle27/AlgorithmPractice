#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())
using vi = vector<int>;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = sz(nums);
        vi dp(n, -1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= nums[i]; j++) {
                if (i + j < n) {
                    if (dp[i + j] < 0) {
                        dp[i + j] = dp[i] + 1;
                    }
                }
                else {
                    break;
                }
            }
        }
        return dp[n - 1];
    }
};

/**
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = sz(nums);
        if (n == 1) return 0;

        int max_reach{-1};
        int res{0};
        int cur_end{0};
        for (int i = 0; i < n; i++) {
            if (i > cur_end) {
                res++;
                cur_end = max_reach;
            }
            max_reach = max(max_reach, i + nums[i]);
            if (max_reach >= n - 1) {
                res++;
                break;
            };
        }
        return res;
    }
};

*/