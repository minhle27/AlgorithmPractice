#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using iii = tuple<int, int, int>;

#define PB push_back
#define MP make_pair
#define LSOne(S) ((S) & -(S))
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define tcT template<class T

#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; i--)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; i++)
#define DEBUG(x)                                                               \
    {                                                                          \
        cout << #x << " = ";                                                   \
        cout << (x) << endl;                                                   \
    }
#define PR(a, n)                                                               \
    {                                                                          \
        cout << #a << " = ";                                                   \
        FOR(_, 1, n) cout << a[_] << ' ';                                      \
        cout << endl;                                                          \
    }
#define PR0(a, n)                                                              \
    {                                                                          \
        cout << #a << " = ";                                                   \
        REP(_, n) cout << a[_] << ' ';                                         \
        cout << endl;                                                          \
    }

// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1};
template<class T>
using pqg = priority_queue<T, vector<T>, greater<T>>; // minheap

tcT > bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
} // set a = min(a,b)
tcT > bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
} // set a = max(a,b)

tcT > T gcd(T a, T b) {
    T r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
tcT > T lcm(T a, T b) { return a / gcd(a, b) * b; }

ll cdiv(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b);
} // divide a by b rounded up
ll fdiv(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
} // divide a by b rounded down

// bitwise ops
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) {                                // assert(x >= 0);
    return x == 0 ? 0 : 31 - __builtin_clz(x);
} // floor(log2(x))
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

struct Node {
    char data;
    Node* next;
    Node* prev;

    Node(char c) : data(c), next(nullptr) {}
};

class CharLL {
private:
    Node* head;
    Node* tail;
    Node* cur;

public:
    CharLL() : head(nullptr), tail(nullptr), cur(nullptr) {
        head = new Node('0');
        tail = new Node('0');
        head->next = tail;
        tail->prev = head;
    }

    void print() const {
        Node* tmp = head->next;
        while (tmp != tail) {
            cout << tmp->data;
            tmp = tmp->next;
        }
        cout << endl;
    }

    void insert(char c) {
        Node* newNode = new Node(c);
        if (cur == nullptr) {
            head->next = newNode;
            newNode->prev = head;
            newNode->next = tail;
            tail->prev = newNode;
            cur = newNode;
            return;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        cur = newNode;
        if (newNode->next == tail) {
            tail->prev = newNode;
        }
    }

    void moveCur(char c) {
        if (c == '[') {
            cur = head;
        } else {
            cur = tail->prev;
        }
    }

    ~CharLL() {
        Node* tmp = head;
        while (tmp != nullptr) {
            Node* next = tmp->next;
            delete tmp;
            tmp = next;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (cin >> s) {
        CharLL str;
        for (char c : s) {
            if (c == '[' || c == ']') {
                str.moveCur(c);
            } else {
                str.insert(c);
            }
        }
        str.print();
    }

    return 0;
}
