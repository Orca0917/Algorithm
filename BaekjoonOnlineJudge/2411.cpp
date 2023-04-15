#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
int a, b;
int board[101][101];
int memo[101][101][201];

int dp(int row, int col, int cur) {
    if (row == 1 && col == m && cur == a) return 1;

    int &ret = memo[row][col][cur];
    if (ret != -1) return ret;

    ret = 0;

    // 위쪽으로 이동
    if (row - 1 >= 1 && board[row - 1][col] != -1)
        ret += dp(row - 1, col, cur + board[row - 1][col]);

    // 오른쪽으로 이동
    if (col + 1 <= m && board[row][col + 1] != -1)
        ret += dp(row, col + 1, cur + board[row][col + 1]);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> a >> b;
    memset(board, 0, sizeof(board));

    for (int i = 0; i < a; ++i) {
        int x, y; cin >> x >> y;
        board[n - x + 1][y] = 1;
    }

    for (int i = 0; i < b; ++i) {
        int x, y; cin >> x >> y;
        board[n - x + 1][y] = -1;
    }

    memset(memo, -1, sizeof(memo));
    cout << dp(n, 1, 0) << "\n";
    
    return 0;
}