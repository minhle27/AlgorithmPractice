using vi = vector<int>;
using ll = long long;
#define sz(x) int((x).size())

class Solution {
public:
    vector<ll> buildpref(const vi& a) {
        int n = sz(a);
        vector<ll> pref(n + 1);
        pref[0] = 0;
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] + a[i - 1];
        }
        return pref;
    }

    int maxSubArrayLen(vector<int>& nums, int k) {
        vector<ll> pref = buildpref(nums);
        ll res = 0;

        unordered_map<ll, ll> m;
        for (int i = 0; i < sz(pref); i++) {
            if (m.count(pref[i] - k) > 0) {
                res = max(res, i - m[pref[i] - k]);
            }
            if (m.count(pref[i]) == 0) {
                m[pref[i]] = i;
            }
        }
        return res;
    }
};
