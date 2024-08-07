#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int N, L, U;

ll count(int x, vector<int>& a) {
    if (x == 0) return 0;
    map<int, int> m;
    ll res = 0;
    int cur_size = 0;
    for (int l = 1, r = 1; r <= N; r++) {
        m[a[r]]++;
        if (m[a[r]] == 1) {
            cur_size++;
        }
        while (l < r && cur_size > x) {
            m[a[l]]--;
            if (m[a[l]] == 0) {
                cur_size--;
            }
            l++;
        }
        res += r - l + 1;
    }
    
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("debug.log", "w", stderr);
    cin >> N >> L >> U;
    vector<int> a(N + 3);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }

    cout << count(U, a) - count(L - 1, a) << endl;
    
    return 0;
}