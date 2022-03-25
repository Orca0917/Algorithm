#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, f;
int board[3001][3001];
int memo[3001][3001];

int dp(int x, int y) {
    if (x == n && y == m) return 0;
    if (x > n || y > m) return 1234567890;

    int &ret = memo[x][y];
    if (ret != -1) return ret;

    ret = min(dp(x + 1, y), dp(x, y + 1)) + 1 - board[x][y];
    return ret = max(0, ret);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(board, 0, sizeof(board));
    memset(memo, -1, sizeof(memo));

    cin >> n >> m >> f;
    for (int i = 0; i < f; ++i) {
        int x, y, a; cin >> x >> y >> a;
        board[x][y] = a;
    }

    cout << dp(1, 1) << "\n";
    return 0;
}