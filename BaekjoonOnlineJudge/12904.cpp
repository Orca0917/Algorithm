/*
 * author: 0917jong
 * date: 2021-12-03
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s, t; cin >> s >> t;

    while (t.length() != s.length()) {
        if (t.back() == 'A') t.pop_back();
        else {
            t.pop_back();
            reverse(t.begin(), t.end());
        }
    }

    cout << (s == t ? 1 : 0) << "\n";
    return 0;
}