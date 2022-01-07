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
        string word;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == ' ') {
                cout << word << " ";
                word = "";
                continue;
            }
            word = s[i] + word;
        }
        cout << word << "\n";
    }
    
    return 0;
}