#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
 
using namespace std;

set<int> s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    set<int> s;

    for (int i = 1; i * i <= 1LL * 1e9; ++i) {
        ll k = i;
        ll square = k * k;
        ll triple = k * k * k;

        s.insert(square);
        if (triple <= 1LL * 1e9) s.insert(triple);
    }

    vector<int> a;
    for (auto it = s.begin(); it != s.end(); it++) {
        a.push_back(*it);
    }

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        cout << upper_bound(a.begin(), a.end(), n) - a.begin() << "\n";
    }
    
    return 0;
}