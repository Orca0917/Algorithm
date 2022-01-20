#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    map<string, int> m;
    while (n--) {
        string title; cin >> title;
        if (m.find(title) != m.end()) m[title]++;
        else m[title] = 1;
    }

    int cnt = 0;
    string ans;

    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second > cnt) {
            ans = it->first;
            cnt = it->second;
        } else if (it->second == cnt) {
            if (ans > it->first)
                ans = it->first;
        }
    }

    cout << ans << "\n";
    return 0;
}