#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<string> v(36);
    for(string &e: v) cin >> e;
    v.push_back(v[0]);

    bool flag = true;
    set<string> s;
    for (int i = 1; i <= 36 && flag; ++i) {
        int diff1 = abs(v[i][0] - v[i - 1][0]);
        int diff2 = abs(v[i][1] - v[i - 1][1]);
        if (diff1 * diff2 == 0 || diff1 + diff2 != 3) flag = false;
        s.insert(v[i]);
    }

    if (s.size() != 36) flag = false;
    
    cout << (flag ? "Valid" : "Invalid");
    
    return 0;
}