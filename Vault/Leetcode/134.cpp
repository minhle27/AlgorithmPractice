#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())
using vi = vector<int>;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = sz(gas);
        int total_gain = 0;
        int cur_gain = 0;
        int start = 0;
        for (int i = 0; i < n; i++) {
            cur_gain += gas[i] - cost[i];
            total_gain += gas[i] - cost[i];
            if (cur_gain < 0) {
                start = i + 1;
                cur_gain = 0;
            }
        }
        if (total_gain < 0) {
            return -1;
        }
        return start;
    }
};