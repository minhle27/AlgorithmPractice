#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
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

struct Person
{
    int id;
    string name;
};

bool option(const Person& A, const Person& B){
    string nameA = A.name.substr(0, 2);
    string nameB = B.name.substr(0, 2);
    if (nameA < nameB || (nameA == nameB) && A.id < B.id){
        return true;
    }
    return false;
}

vector<Person> a;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; string name;

    while(true){
        cin >> n;
        cin.ignore();
        a.resize(n);
        if (n == 0){
            break;
        }
        for (int i = 0; i < n; i++){
            cin >> name;
            Person p;
            p.id = i; p.name = name;
            a[i] = p;
        }

        sort(a.begin(), a.end(), option);

        for (int i = 0; i < n; i++){
            cout << a[i].name << endl;
        }
        cout << endl;
    }

    return 0;
}