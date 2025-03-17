#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define sz(x) int((x).size())
#define DEBUG(x)                                                               \
    {                                                                          \
        cout << #x << " = " << (x) << endl;                                    \
    }
class Solution {
  public:
    int res = 1e9 + 7;

    bool isOk(const vi &needs, const vi &offer) {
        for (int i = 0; i < sz(needs); i++) {
            if (needs[i] < offer[i]) {
                return false;
            }
        }
        return true;
    }

    void choose(int cur, const vi &price, const vector<vi> &special, int latest, vi needs) {
        for (int i = 0; i < sz(needs); i++) {
            cur += needs[i] * price[i];
        }
        res = min(res, cur);
        for (int i = 0; i < sz(needs); i++) {
            cur -= needs[i] * price[i];
        }

        for (int i = latest; i < sz(special); i++) {
            if (isOk(needs, special[i])) {
                for (int j = 0; j < sz(needs); j++) {
                    needs[j] -= special[i][j];
                }
                cur += special[i][sz(needs)];
                choose(cur, price, special, i, needs);
                cur -= special[i][sz(needs)];
                for (int j = 0; j < sz(needs); j++) {
                    needs[j] += special[i][j];
                }
            }
        }
    }

    int shoppingOffers(vector<int> &price, vector<vector<int>> &special,
                       vector<int> &needs) {
        choose(0, price, special, 0, needs);
        return res;
    }
};
