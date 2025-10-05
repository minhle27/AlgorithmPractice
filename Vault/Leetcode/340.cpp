#define sz(x) int((x).size())
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int l = 0;
        int n = sz(s);
        map<char, int> cnt;
        int num = 0;
        int res = 0;
        for (int r = 0; r < n; r++) {
            cnt[s[r]]++;
            if (cnt[s[r]] == 1)
                num++;
            while (num > k) {
                cnt[s[l]]--;
                if (cnt[s[l]] == 0)
                    num--;
                l++;
            }
            res = max(res, r - l + 1);
        }
        return res;
    }
};
