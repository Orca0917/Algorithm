#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
int board[65][65];
int memo[65][65];

int dp(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > n || board[x][y] == 0) return 0;
    if (x == n && y == n) return 1;

    int &ret = memo[x][y];
    if (ret != -1) return ret;

    // 가로로 이동
    ret = max(dp(x + board[x][y], y), dp(x, y + board[x][y]));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));

    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> board[i][j];

    int ret = dp(1, 1);
    if (ret == 0) cout << "Hing";
    else cout << "HaruHaru";
    
    return 0;
}