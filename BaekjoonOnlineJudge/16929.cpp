#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

char board[51][51];
bool vis[51][51];
int n, m; 
int mv[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool dfs(int x, int y, char c) {
    vis[x][y] = true;

    bool result = false;
    int vis_cnt = 0;
    for (int i = 0; i < 4; ++i) {
        int nx = x + mv[i][0];
        int ny = y + mv[i][1];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] != c) continue;
        if (vis[nx][ny]) {
            vis_cnt += 1;
            continue;
        }
        result |= dfs(nx, ny, c);
    }
    
    if (vis_cnt >= 2) return true;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(vis, false, sizeof(vis));

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];
    
    bool answer = false;
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < m; ++j)
            if (!vis[i][j] && dfs(i, j, board[i][j])) {
                answer = true;
                goto out;
            }

out:
    cout << (answer ? "Yes" : "No");

    return 0;
}