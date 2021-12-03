#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        int x, y; cin >> x >> y;
        if (x > y) {
            cout << x + y << "\n";
        } else {
            cout << y - (y % x) / 2 << "\n";
        }
    }
    return 0;
}