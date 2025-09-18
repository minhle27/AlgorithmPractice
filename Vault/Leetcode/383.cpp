#define sz(x) int((x).size())
using vi = vector<int>;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int sz_ransom = sz(ransomNote);
        int sz_mag = sz(magazine);

        vi cnt_ransom(26);
        vi cnt_mag(26);

        for (int i = 0; i < sz_ransom; i++) {
            cnt_ransom[ransomNote[i] - 'a']++;
        }
        for (int i = 0; i < sz_mag; i++) {
            cnt_mag[magazine[i] - 'a']++;
        }

        for (int i = 0; i < 26; i++) {
            if (cnt_ransom[i] > cnt_mag[i]) {
                return false;
            }
        }
        return true;
    }
};
