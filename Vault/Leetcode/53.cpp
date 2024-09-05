#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int(x.size())

class Solution {
public:
    vi buildPref(vi& a) {
        int sz_a = sz(a);
        vi pref(sz_a + 1);
        pref[0] = 0;
        pref[1] = a[0];
        for (int i = 2; i <= sz_a; i++) {
            pref[i] = pref[i - 1] + a[i - 1];
        }
        return pref;
    }

    int maxSubArray(vector<int>& nums) {
        int n = sz(nums);
        vi pref = buildPref(nums);

        int sz_pref = sz(pref);
        int res = -1e9 - 7;
        int i = 0;

        for (int j = 1; j < sz_pref; j++) {
           if (pref[j] - pref[i] > res) {
            res = pref[j] - pref[i];
           } 
           if (pref[j] < pref[i]) {
            i = j;
           }
        }
        return res;
    }
};