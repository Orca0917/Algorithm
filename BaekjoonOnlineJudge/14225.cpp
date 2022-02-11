#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> v;
set<int> s;
int n;

void bf(int index, int sum) {
    if (index == n) {
        // cout << "insert " << sum << "\n";
        s.insert(sum);
    } else {
        bf(index + 1, sum);
        bf(index + 1, sum + v[index]);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    v.resize(n);
    for (int &e : v) cin >> e;

    bf(0, 0);
    s.erase(0);
    int targ = 1;
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (*(it) == targ) ++targ;
        else break;
    }

    cout << targ << "\n";

    return 0;
}