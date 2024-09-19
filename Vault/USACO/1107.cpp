#include <bits/stdc++.h>
using namespace std;

#define sz(x) int(x.size())
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
using ll = long long;
using vi = vector<int>;

int main() {
    int n;
    cin >> n;

    vector<vector<string>> v;

    for (int i = 0; i < n; i++) {
        vector<string> rel(8);
        for (int j = 0; j < 8; j++) {
            cin >> rel[j];
        }
        v.push_back({rel[0], rel[3], rel[4], rel[7]});
    }

    map<string, int> order = {
        {"Ox", 1},
        {"Tiger", 2},
        {"Rabbit", 3},
        {"Dragon", 4},
        {"Snake", 5},
        {"Horse",6},
        {"Goat", 7},
        {"Monkey", 8},
        {"Rooster", 9},
        {"Dog", 10},
        {"Pig", 11},
        {"Rat", 12},
    };
    map<string, int> m;
    map<string, string> year;
    m[v[0][3]] = 0;
    year["Bessie"] = "Ox";

    for (auto rel: v) {
        string animal1 = rel[0];
        string animal2 = rel[3];
        string year1 = rel[2];
        string year2 = year[animal2];
        year[animal1] = year1;

        int dis = abs(order[year1] - order[year2]);
        if (rel[1] == "next") {
            if (order[year2] < order[year1]) {
                m[animal1] = m[animal2] + dis;
            } else {
                m[animal1] = m[animal2] + 12 - dis;
            }
        } else {
            if (order[year2] <= order[year1]) {
                m[animal1] = m[animal2] - 12 + dis;
            } else {
                m[animal1] = m[animal2] - dis;
            }
        }
    }

    cout << abs(m["Elsie"] - m["Bessie"]) << endl;
    return 0;
}