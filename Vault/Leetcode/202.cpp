#include <bits/stdc++.h>
using namespace std;

using vb = vector<bool>;

class Solution {
public:
    bool solve(int n, vb& v) {
        if (n == 1) return true;
        int next{0};
        while (n > 0) {
            int last = n % 10;
            next += last * last; n /= 10;
        }
        if (v[next]) return false;
        v[next] = true;
        return solve(next, v);
    }
    bool isHappy(int n) {
        vb v = vb(1000, false);
        return solve(n, v);
    }
};
