#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int convert(char c) {
    if (c == ' ') return 3;
    else if ('0' <= c && c <= '9') return 2;
    else if ('A' <= c && c <= 'Z') return 1;
    else return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    while (getline(cin, s)) {
        vector<int> cnt(4, 0);
        for (int i = 0; i < s.length(); ++i) {
            cnt[convert(s[i])]++;
        }
        for (int e : cnt) cout << e << " ";
        cout << "\n";
    }
    return 0;
}