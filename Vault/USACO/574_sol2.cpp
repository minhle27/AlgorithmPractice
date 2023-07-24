#include <bits/stdc++.h>
using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    freopen("feast.in", "r", stdin);
	freopen("feast.out", "w", stdout);

	int T, A, B;
	cin >> T >> A >> B;

    if (A < B) {
        swap(A, B);
    }

    int D = A / 2;
    int E = B / 2;
    priority_queue<int> maxHeap;
    int maxie = 0;
    for (int x = 0; x <= T / A; x++) {
        int y = (T - A * x) / B;
        if ((y * B + A * x) <= T) {
        	maxie = max(maxie, (y * B + A * x));
        }
		if (T - A*x - D >= 0 && A <= T) {
            y = (T - A * x - D) / B;
            if ((y * B + A * x + D) <= T) {
               maxie = max(y * B + A * x + D, maxie);
            }
        }
		
        if (T - A*x - E >= 0 && B <= T ) {
            y = (T - A * x - E) / B;
            if ((y * B + A * x + E) <= T) {
                maxie = max((y * B + A * x + E), maxie);
            }
        }

        if (T - A*x - D - E >= 0 && B + A <= T) {
            y = (T - A * x - D - E) / B;
            if ((y * B + A * x + E + D) <= T) {
               maxie = max((y * B + A * x + E + D), maxie);
            }
        }
    }

    cout << maxie << endl;
    return 0;
}
