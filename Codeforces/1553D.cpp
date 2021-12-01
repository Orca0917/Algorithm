#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        string s, t; cin >> s >> t;
        int si = s.length() - 1;
        int ti = t.length() - 1;

        while (si >= 0 && ti >= 0) {
            if (s[si] == t[ti]) {
                --si;
                --ti;
            } else {
                si -= 2;
            }
        }

        if (ti < 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}