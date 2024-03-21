#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int board[100][100];
bool vis[100][100];
int n, m, k;
pii moves[4] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int dfs(int x, int y) {
    vis[x][y] = true;

    int ret = 1;
    for (pii mv : moves) {
        int nx = x + mv.first;
        int ny = y + mv.second;

        if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny]) continue;
        if (board[nx][ny] == 0) continue;

        ret += dfs(nx, ny);
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(vis, false, sizeof(vis));
    memset(board, 0, sizeof(board));

    cin >> n >> m >> k;

    while (k--) {
        int x, y; cin >> x >> y;
        board[x - 1][y - 1] = 1;
    }

    int answer = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) 
            if (!vis[i][j] && board[i][j] == 1) {
                answer = max(answer, dfs(i, j));
            }

    cout << answer << "\n";

    
    return 0;
}