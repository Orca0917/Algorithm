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
        int n; cin >> n;
        string s; cin >> s;

        bool flag = false;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 2; j < n; ++j) {
                if (s[i] == s[j] && s[i + 1] == s[j + 1]) {
                    flag = true;
                    goto out;
                }
            }
        }

    out:
        if (flag) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}