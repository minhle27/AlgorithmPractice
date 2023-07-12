#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pi;
typedef tuple<int, int, int> iii;

#define f first
#define s second
#define PB push_back
#define MP make_pair

#define LSOne(S) ((S) & -(S))
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int N;

vl psum(const vl &a){
    vl psum(sz(a) + 1);
    for (int i = 0; i < sz(a); i++) {
        psum[i + 1] = psum[i] + a[i];
    }
    return psum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    cin >> N;
    vl a(N);
    for (ll &x : a) cin >> x;
    vl ps = psum(a);
    ll res = 0;
    for (ll l = 1; l <= N; l++){
        for (ll r = l + res; r <= N; r++){
            if ((ps[r] - ps[l - 1]) % 7 == 0){
                res = max(res, r - l + 1);
            }
        }
    }

    cout << res << endl;

    return 0;
}