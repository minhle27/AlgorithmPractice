#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

struct DSU {
    vi lab;
    int max_sz;
    DSU(int n) { 
        lab = vi(n, -1); 
        max_sz = 1;
    }

    int get(int x) { return lab[x] < 0 ? x : lab[x] = get(lab[x]); }

    bool same_set(int a, int b) { return get(a) == get(b); }

    bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (lab[x] > lab[y]) swap(x, y);
		lab[x] += lab[y];
		lab[y] = x;
        max_sz = max(max_sz, -lab[x]);
		return true;
	}
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 0) return 0;
        map<int, int> m;
        DSU dsu(n);
        int node = 0;
        for (auto num : nums) {
            if (m.count(num) > 0) continue;
            m[num] = node; node++;
            if (m.count(num + 1) > 0) {
                dsu.unite(m[num], m[num + 1]);
            }
            if (m.count(num - 1) > 0) {
                dsu.unite(m[num], m[num - 1]);
            }
        }
        return dsu.max_sz;
    }
};