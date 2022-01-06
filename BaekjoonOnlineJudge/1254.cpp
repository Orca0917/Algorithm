#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool isPalin(string &s, int l, int r) {
    if (r <= l) return true;

    if (s[l] == s[r]) return isPalin(s, l + 1, r - 1);
    else return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    
    int cnt = 0;
    for (int i = 0; i < s.length(); ++i)
        if (isPalin(s, i, s.length() - 1)) break;
        else ++cnt;

    cout << s.length() + cnt << "\n";
    return 0;
}