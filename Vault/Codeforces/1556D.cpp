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

int ask(string s, int a, int b) {
	cout << s << ' ' << a << ' ' << b << endl;
	int res;
	cin >> res;
	return res;
}

int sum(int a, int b) {
	int and_ = ask("and", ++a, ++b);
	int or_ = ask("or", a, b);

	int xor_ = ~and_ & or_;  

	return 2 * and_ + xor_;  
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
	int n, k;
	cin >> n >> k;

	int a_plus_b = sum(0, 1);
	int a_plus_c = sum(0, 2);
	int b_plus_c = sum(1, 2);

	vector<int> arr{(a_plus_b + a_plus_c - b_plus_c) / 2};
	arr.push_back(a_plus_b - arr[0]);
	arr.push_back(a_plus_c - arr[0]);

	for (int i = 3; i < n; i++) { arr.push_back(sum(i - 1, i) - arr.back()); }

	sort(arr.begin(), arr.end());
	cout << "finish " << arr[k - 1] << endl;
}
