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
        if (s.length() % 2) cout << "NO\n";
        else {
            bool result = true;
            int idx = s.length() / 2;

            for (int i = 0; i < s.length() / 2 && result; ++i)
                if (s[i] != s[i + idx])
                    result = false;

            if (result) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    
    return 0;
}