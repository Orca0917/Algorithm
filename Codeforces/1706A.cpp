#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n, m; cin >> n >> m;

        string s;
        for (int i = 0; i <= m; ++i) s += "B";

        for (int i = 0; i < n; ++i) {
            int idx; cin >> idx;
            idx = min(idx, m + 1 - idx);
            if (s[idx] == 'A') s[m + 1 - idx] = 'A';
            else s[idx] = 'A';
        }

        for (int i = 1; i <= m; ++i) cout << s[i];
        cout << "\n";
    }

    return 0;
}