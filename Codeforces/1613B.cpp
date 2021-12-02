/* 
 * author: 0917jong
 * date: 2021-12-01
 */

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.begin(), a.end());
        for (int i = 0; i < n / 2; ++i) {
            cout << a[n - i - 1] << " " << a[0] << "\n";
        }
    }
    return 0;
}