#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    set<char> pokemons;
    for (auto pok: s) {
        pokemons.insert(pok);
    }

    int total = sz(pokemons);
    int i = 0; 
    int res = 1e9;
    map<char, int> cnt;
    for (int j = 0; j < n; j++) {
        cnt[s[j]]++;
        while (i < j && cnt[s[i]] > 1) {
            cnt[s[i]]--;
            i++;
        }
        if (sz(cnt) == total) {
            res = min(res, j - i + 1);
        }
    }

    cout << res << endl;

    return 0;
}

