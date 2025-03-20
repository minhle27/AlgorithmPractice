#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
    int area() { return (y2 - y1) * (x2 - x1); }
};

int intersect(Rect p, Rect q) {
    int xOverlap = max(0, min(p.x2, q.x2) - max(p.x1, q.x1));
    int yOverlap = max(0, min(p.y2, q.y2) - max(p.y1, q.y1));
    return xOverlap * yOverlap;
}

int main() {
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);

    Rect lm, cf;
    cin >> lm.x1 >> lm.y1 >> lm.x2 >> lm.y2;
    cin >> cf.x1 >> cf.y1 >> cf.x2 >> cf.y2;

    if (lm.y1 >= cf.y1 && lm.y2 <= cf.y2) {
        if (lm.x1 < cf.x1 && lm.x2 > cf.x2) {
            cout << lm.area();
        } else {
            cout << lm.area() - intersect(lm, cf);
        }
    } else if (lm.x1 >= cf.x1 && lm.x2 <= cf.x2) {
        if (lm.y1 < cf.y1 && lm.y2 > cf.y2) {
            cout << lm.area();
        } else {
            cout << lm.area() - intersect(lm, cf);
        }
    } else {
        cout << lm.area() << endl;
    }
}
