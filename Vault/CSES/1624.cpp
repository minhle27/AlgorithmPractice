#include <bits/stdc++.h>
using namespace std;

vector<bool> isFreeCol(8, true);
map<int, bool> ENWS;
map<int, bool> WNES;

int res = 0;
vector<string> v;

void place(int row, int col) {
    isFreeCol[col] = false;
    ENWS[row + col] = false;
    WNES[row - col] = false;
}

void remove(int row, int col) {
    isFreeCol[col] = true;
    ENWS[row + col] = true;
    WNES[row - col] = true;
}

void backtrack(int row) {
    if (row == 8) {
        res++;
        return;
    }
    for (int j = 0; j < 8; j++) {
        if (isFreeCol[j] && ENWS[row + j] && WNES[row - j] && v[row][j] != '*') {
            place(row, j);
            backtrack(row + 1);
            remove(row, j);
        }
    }
}

int main() {
    for (int i = 0; i < 8; i++) {
        string cur;
        cin >> cur;
        v.push_back(cur);
    }

    for (int i = 0; i <= 14; i++) ENWS[i] = true;
    for (int i = -7; i <= 7; i++) WNES[i] = true;

    backtrack(0);
    cout << res << endl;
}
