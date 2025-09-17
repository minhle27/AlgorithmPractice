using vi = vector<int>;

class Solution {
public:
    bool compare(const vi& a, const vi& b) {
        vi num1;
        num1.reserve(a.size() + b.size());
        vi num2;
        num2.reserve(a.size() + b.size());

        num1.insert(num1.end(), a.begin(), a.end());
        num1.insert(num1.end(), b.begin(), b.end());
        num2.insert(num2.end(), b.begin(), b.end());
        num2.insert(num2.end(), a.begin(), a.end());

        int m = int(a.size() + b.size());
        for (int i = 0; i < m; ++i) {
            if (num1[i] < num2[i])
                return false;
            if (num1[i] > num2[i])
                return true;
        }
        return false;
    }

    string largestNumber(vector<int>& nums) {
        int n = int(nums.size());
        vector<vi> v;
        for (int i = 0; i < n; i++) {
            vi cur;
            int num = nums[i];
            if (num == 0)
                cur.push_back(0);
            while (num > 0) {
                cur.push_back(num % 10);
                num /= 10;
            }
            reverse(cur.begin(), cur.end());
            v.push_back(cur);
        }
        sort(v.begin(), v.end(),
             [this](const vi& a, const vi& b) { return compare(a, b); });

        string res = "";
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                res += '0' + v[i][j];
            }
            if (res == "0")
                break;
        }
        return res;
    }
};
