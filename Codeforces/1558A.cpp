#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        int a, b; cin >> a >> b;
        if (a < b) swap (a, b);
        // assert(a > b);
        int minLen = min(a, b);
        int over = a - minLen;
        int total = a + b;

        set<int> s;
        if (over % 2) {
            for (int i = 0; i <= minLen * 2; i += 2) {
                s.insert(i + over / 2);
                s.insert(i + (over + 1) / 2);
            }
        } else {
            for (int i = 0; i <= minLen * 2; i += 2) {
                s.insert(i + over / 2);
            }
        }
        cout << s.size() << "\n";
        for (auto it = s.begin(); it != s.end(); ++it) cout << *it << " ";
        cout << "\n";
    }
    return 0;
}