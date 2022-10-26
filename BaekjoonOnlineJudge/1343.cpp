#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    string answer;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '.') {
            answer += ".";
            continue;
        }


        if (i + 3 < s.length() && s[i + 1] == 'X' && s[i + 1] == s[i + 2] && s[i + 2] == s[i + 3]) {
            i += 3;
            answer += "AAAA";
        }
            
        else if (i + 1 < s.length() && s[i + 1] == 'X') {
            i += 1;
            answer += "BB";
        }
        else {
            answer = "-1";
            break;
        }
    }

    cout << answer << "\n";
    
    return 0;
}