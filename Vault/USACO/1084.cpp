#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
#define sz(x) int((x).size())

int main() {
    int n;
    cin >> n;
    int ecnt{0};
    int ocnt{0};
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        if (num % 2 == 0) {
            ecnt++;
        } else {
            ocnt++;
        }
    }

    int eo = min(ecnt, ocnt);
    if (ecnt >= ocnt) {
        cout << eo * 2 + 1 << endl;   
        return 0;
    } else {
        int oleft = ocnt - ecnt;
        int totaleo = eo + oleft / 3;
        oleft = oleft % 3;

        if (oleft == 0) {
            cout << totaleo * 2 << endl;
        } else if (oleft == 1) {
            cout << (totaleo - 1) * 2 + 1 << endl;
        } else if (oleft == 2) {
            cout << totaleo * 2 + 1 << endl;
        }
    }
}
