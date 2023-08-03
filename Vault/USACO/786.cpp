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

struct Point {
    int time;
    int id;
    bool is_start;
    bool operator<(const Point &y) {
        return time < y.time;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int n;
    cin >> n;
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        points.PB({a, i, true});
        points.PB({b, i, false});
    }
    
    sort(points.begin(), points.end());

    int prev = 0, cur = 0, total = 0;
    set<int> working;
    vi alone_time(n, 0);

    for (auto &p : points) {
        cur = p.time;
        if (working.size() > 0) total += cur - prev;
        if (working.size() == 1) alone_time[*working.begin()] += cur - prev;
        if (p.is_start) {
            working.insert(p.id);
        }
        else {
            working.erase(p.id);
        }
        prev = cur;
    }

    cout << total - *min_element(alone_time.begin(), alone_time.end()) << endl;

    
    return 0;
}