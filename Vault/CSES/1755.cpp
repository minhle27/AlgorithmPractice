#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >> s;
    int freq[26] = {0};
    for (auto c : s) freq[c-'A']++;
    int oddCount = 0, oddIdx = -1;
    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2 == 1) {
            oddIdx = i;
            oddCount++;
            if (oddCount > 1) {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
        }
    }
    
    string res="", postString="";
    for (int i = 0; i < 26; i++) {
        if (i != oddIdx && freq[i] > 0) {
            for (int j = 0; j < freq[i]/2; j++) {
                res += (i+'A');
                postString += (i+'A');
            }
        }
    }
    
    if (oddIdx != -1) {
        for (int i = 0; i < freq[oddIdx]; i++) {
            res += oddIdx+'A';
        }
    }
    for (int i = postString.size()-1; i >= 0; i--) {
        res += (postString[i]);
    }
    cout << res << endl;
    return 0;
}