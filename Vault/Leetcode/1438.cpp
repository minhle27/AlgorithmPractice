#define sz(x) int((x).size())
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int l = 0;
        multiset<int> ms;
        int res = 0;
        int n = sz(nums);
        for (int r = 0; r < n; r++) {
            ms.insert(nums[r]);
            while (*ms.rbegin() - *ms.begin() > limit) {
                auto it = ms.find(nums[l]);
                ms.erase(it);
                l++;
            }
            cout << l << " " << r << endl;
            res = max(res, r - l + 1);
        }
        return res;
    }
};
