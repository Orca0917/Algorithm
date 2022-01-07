#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<string> v;
    string s;

    for (int i = 0; i < n; ++i) {
        cin >> s;
        string number = "";

        for (int j = 0; j < s.length(); ++j) {
            if ('0' <= s[j] && s[j] <= '9') {
                if (number.length() == 1 && number[0] == '0' && s[j] == '0') continue;
                number += s[j];
            }
            else {
                if (number.length() > 1 && number[0] == '0') number.erase(0, 1);
                if (!number.empty()) v.push_back(number);
                number.clear();
            }
        }

        if (number.length() > 0) {
            if (number.length() > 1 && number[0] == '0') number.erase(0, 1);
            if (!number.empty()) v.push_back(number);
            number.clear();
        }
    }

    sort(v.begin(), v.end(), [](const string &a, const string &b) {
        if (a.length() == b.length()) return a.compare(b) < 0;
        return a.length() < b.length();
    });

    for (string e : v) cout << e << "\n";
    return 0;
}