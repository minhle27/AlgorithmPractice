#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        int res = 0;
        int n = sz(tokens);
        int i = 0, j = n - 1;
        bool flag = false;
        while (i <= j) {
            if (power >= tokens[i]) {
                res++;
                power -= tokens[i];
                i++;
                if (flag) flag = false;
            }
            else if (res >= 1) {
                res--;
                power += tokens[j];
                j--;
                flag = true;
            }
            else if (flag) {
                res++;
                return res;
            }
            else {
                return res;
            }
        }
        if (flag) res++;
        return res;
    }
};
