#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    getline(cin, s);
    bool tag = false;
    vector<char> v;
    for (char c : s) {
        if (c == '<') {
            for (int i = v.size() - 1; i >= 0; --i) cout << v[i];
            v.clear();
            tag = true;
            cout << c;
        }
        else if (c == '>') {
            tag = false;
            cout << c;
        }
        else if (c == ' ') {
            for (int i = v.size() - 1; i >= 0; --i) cout << v[i];
            v.clear();
            cout << ' ';
        }

        else if (tag) cout << c;
        else v.push_back(c);
    }
    
    for (int i = v.size() - 1; i >= 0; --i) cout << v[i];

    return 0;
}