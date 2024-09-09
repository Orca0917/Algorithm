#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<char> g(200, '#');

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n1, n2; cin >> n1 >> n2;
    string s1, s2; cin >> s1 >> s2;
    reverse(s1.begin(), s1.end());

    int T; cin >> T;
    for (int i = 0; i < n1; ++i) g[100 + i * 2] = s1[i];
    for (int i = 0; i < n2; ++i) g[101 + (n1 - 1) * 2 - 2 * T + i * 2] = s2[i];

    for (int i = 0; i < 200; ++i)
        if (g[i] == '#') continue;
        else cout << g[i];
    
    return 0;
}