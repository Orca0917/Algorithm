#include <bits/stdc++.h>
using namespace std;
string s, t; 

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        cin >> s >> t;
        bool flag = false;
        for (int i = 0; i < s.length() && !flag; ++i) {
            if (s[i] == t[0]) {
                // order: [i, rev] + [rev + 1, left];
                for (int rev = i; rev < s.length(); ++rev) {
                    string made;
                    for (int si = i; si <= rev && si < s.length(); ++si) made += s[si];
                    for (int si = rev - 1; made.length() < t.length() && si >= 0; --si) made += s[si];
                    if (made == t) flag = true;
                }
            }
        }

        cout << (flag ? "YES" : "NO") << "\n";
    }
    return 0;
}