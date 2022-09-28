#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    int tc = 1;
    while (testcase--) {
        string s; cin >> s;
        int k; cin >> k;

        int answer = 0;
        for (int i = 0; i <= s.length() - k; ++i) {
            if (s[i] == '+') continue;
            ++answer;
            for (int j = i; j < i + k; ++j) s[j] ^= ('+' ^ '-');
        }

        for (char c : s) if (c == '-') answer = -1;

        cout << "Case #" << tc++ << ": ";
        if (answer == -1) cout << "IMPOSSIBLE" << "\n";
        else cout << answer << "\n";
    }
    
    return 0;
}