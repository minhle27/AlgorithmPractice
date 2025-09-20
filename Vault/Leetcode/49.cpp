class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        map<string, vector<string>> m;
        for (int i = 0; i < strs.size(); i++) {
            string cur = strs[i];
            sort(cur.begin(), cur.end());
            m[cur].push_back(strs[i]);
        }

        for (const auto& it : m) {
            res.push_back(it.second);
        }
        return res;
    }
};
