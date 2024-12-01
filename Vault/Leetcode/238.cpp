using vi = vector<int>;
#define sz(x) int((x).size())

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = sz(nums);
        vi pref(n + 1), suf(n + 2);
        pref[0] = 1; suf[n + 1] = 1;
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] * nums[i - 1];
            suf[n + 1 - i] = suf[n + 2 - i] * nums[n - i];
        }        
        vi res;
        for (int i = 1; i <= n; i++) {
            res.push_back(pref[i - 1] * suf[i + 1]);
        }
        return res;
    }
};

