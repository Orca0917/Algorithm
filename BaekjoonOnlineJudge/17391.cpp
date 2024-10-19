#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int board[301][301];
int memo[301][301];
int n, m;

int dp(int x, int y) {
    if (x > n || y > m) return 1e9;
    if (x == n && y == m) return 0;

    int &ret = memo[x][y];
    if (ret != -1) return ret;

    ret = 1e9;
    int fuel = board[x][y];
    for (int i = 1; i <= fuel; ++i) {
        ret = min({ret, 1 + dp(x + i, y), 1 + dp(x, y + i)});
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> board[i][j];

    cout << dp(1, 1);
    
    
    return 0;
}