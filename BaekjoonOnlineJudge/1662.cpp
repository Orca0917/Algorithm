#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<bool> vis(51, false);
string s; 

int bruteforce(string &s, int index) {
    int ret = 0;

    for (int i = index; i < s.length(); ++i) {
        if (s[i] == '(' && !vis[i]) {
            vis[i] = true;
            int rep = s[i - 1] - '0';
            --ret;
            ret += rep * bruteforce(s, i + 1);
        } else if (s[i] == ')' && !vis[i]) {
            vis[i] = true;
            return ret;
        } else if (!vis[i]) {
            vis[i] = true;
            ++ret;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s;

    cout << bruteforce(s, 0) << "\n";
    
    return 0;
}