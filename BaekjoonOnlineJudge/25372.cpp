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
        string s; cin >> s;
        if (6 <= s.length() && s.length() <= 9) cout << "yes\n";
        else cout << "no\n";
    }
    
    return 0;
}