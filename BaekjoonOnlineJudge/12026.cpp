#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N;
string s;
int memo[1001][3];

map<char, int> m;

int dp(int n, char c) {
    if (n > N) return 1e7;
    else if (n == N) return 0;

    int &ret = memo[n][m[c]];
    if (ret != -1) return ret;

    char target;
    if (c == 'B') target = 'O';
    else if (c == 'O') target = 'J';
    else if (c == 'J') target = 'B';

    ret = 1e7;
    for (int i = 1; n + i <= N; ++i) {
        if (s[n + i] == target)
            ret = min(ret, dp(n + i, target) + i * i);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> s;
    s = "." + s;

    m['B'] = 0;
    m['O'] = 1;
    m['J'] = 2;

    memset(memo, -1, sizeof(memo));
    cout << (dp(1, 'B') == 1e7 ? -1 : dp(1, 'B')) << "\n";

    return 0;
}