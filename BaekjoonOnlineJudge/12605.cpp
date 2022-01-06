#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int id = 1;
    int testcase; cin >> testcase;
    string s; getline(cin, s);
    while (testcase--) {
        cout << "Case #" << id++ << ": ";
        getline(cin, s);
        string word;
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] == ' ') {
                cout << word << " ";
                word = "";
            } else {
                word = s[i] + word;
            }
        }
        cout << word << "\n";
    }
    
    return 0;
}