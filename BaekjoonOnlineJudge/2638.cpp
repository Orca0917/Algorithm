#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int board[101][101];
int mv[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

bool cheese() {
    bool ret = false;

    queue<pii> q;
    q.push({0, 0});
    
    bool vis[101][101];
    memset(vis, false, sizeof(vis));

    vis[0][0] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + mv[i][0];
            int ny = y + mv[i][1];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (vis[nx][ny]) continue;

            if (board[nx][ny] >= 1) {
                board[nx][ny] += 1;
                continue;
            }

            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] >= 3) {
                board[i][j] = 0;
                ret = true;
            } else if (board[i][j] != 0) {
                board[i][j] = 1;
            }

    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    int result = 0;
    while(cheese()) ++result;

    cout << result << "\n";

    return 0;
}