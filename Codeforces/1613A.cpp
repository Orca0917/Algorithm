/* 
 * author: 0917jong
 * date: 2021-12-01
 */

#include <bits/stdc++.h>
using namespace std;
int len(int num) {
    int len = 0;
    while (num > 0) {
        num /= 10;
        ++len;
    }
    return len;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        int x1, p1; cin >> x1 >> p1;
        int x2, p2; cin >> x2 >> p2;
 
        int x1Len = len(x1);
        int x2Len = len(x2);
 
        if (x1Len + p1 == x2Len + p2) {
            if (x1Len < x2Len) {
                for (int i = x1Len; i < x2Len; ++i)
                    x1 *= 10;
            } else if (x1Len > x2Len) {
                for (int i = x2Len; i < x1Len; ++i)
                    x2 *= 10;
            }
 
            if (x1 > x2) cout << ">" << "\n";
            else if (x1 == x2) cout << "=" << "\n";
            else cout << "<" << "\n";
        } else {
            if (x1Len + p1 > x2Len + p2) cout << ">" << "\n";
            else cout << "<" << "\n";
        }
    }
    return 0;
}