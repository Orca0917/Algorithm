#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    string s; getline(cin, s);
    while (testcase--) {
        getline(cin, s);
        s = s.substr(0, s.length());
        int blankCnt = 0, i;
        string word;
        for (i = 0; i < s.length(); ++i) {
            if (s[i] == ' ') ++blankCnt;
            if (blankCnt == 2) break;
            word += s[i];
        }

        cout << s.substr(i + 1) + " " + word << "\n";
    }
    
    return 0;
}