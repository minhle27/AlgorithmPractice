#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int n = sz(people);
        int i = 0, j = n - 1;
        int res = 0;
        while (i < j) {
            if (people[i] + people[j] <= limit) {
                i++; j--; res++;
            } else {
                j--; res++;
            }
        }
        if (i == j) res++;
        return res;
    }
};
