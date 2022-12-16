#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
string s1, s2;
int memo[1001][1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> s1 >> m >> s2;
    memset(memo, 0, sizeof(memo));

    int result = 0;
    int x, y;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) memo[i][j] = memo[i - 1][j - 1] + 3;
            memo[i][j] = max(memo[i][j], max({memo[i - 1][j - 1], memo[i - 1][j], memo[i][j - 1]}) - 2);
            if (result < memo[i][j]) result = memo[i][j], x = i, y = j;
        }
    }

    vector<char> res1, res2;
    while (x > 0 && y > 0) {
        if (memo[x][y] == 0) break;
        res1.push_back(s1[x - 1]);
        res2.push_back(s2[y - 1]);

        if (memo[x][y] == memo[x - 1][y] - 2) {
            res2.pop_back();
            x -= 1;
        }

        else if (memo[x][y] == memo[x][y - 1] - 2) {
            res1.pop_back();
            y -= 1;
        }

        else {
            x -= 1;
            y -= 1;
        }
    }

    cout << result << "\n";
    for (auto it = res1.rbegin(); it != res1.rend(); ++it) cout << *it; cout << "\n";
    for (auto it = res2.rbegin(); it != res2.rend(); ++it) cout << *it; cout << "\n";

    return 0;
}