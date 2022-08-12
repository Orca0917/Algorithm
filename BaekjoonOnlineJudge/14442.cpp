#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Q {
    int x;
    int y;
    int broke_cnt;
    int move_cnt;
};

int n, m, k;
int board[1001][1001];
bool vis[1001][1001][11];

int bfs(int x, int y, int cnt) {
    queue<Q> q;
    q.push({x, y, cnt, 1});
    vis[x][y][cnt] = true;

    int ret = -1;
    while (!q.empty()) {
        Q here = q.front(); q.pop();

        if (here.x == n - 1 && here.y == m - 1) {
            ret = here.move_cnt;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int there_x = here.x + "2101"[i] - '0' - 1;
            int there_y = here.y + "1210"[i] - '0' - 1;

            if (there_x < 0 || there_y < 0 || there_x >= n || there_y >= m) continue;
            if (board[there_x][there_y] == 1 && here.broke_cnt < k) {
                if (vis[there_x][there_y][here.broke_cnt + 1]) continue;
                vis[there_x][there_y][here.broke_cnt + 1] = true;
                q.push({there_x, there_y, here.broke_cnt + 1, here.move_cnt + 1});
            } else if (board[there_x][there_y] == 0) {
                if (vis[there_x][there_y][here.broke_cnt]) continue;
                vis[there_x][there_y][here.broke_cnt] = true;
                q.push({there_x, there_y, here.broke_cnt, here.move_cnt + 1});
            }
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            board[i][j] = c - '0';
        }

    memset(vis, false, sizeof(vis));
    int ret = bfs(0, 0, 0);
    cout << ret << "\n";

    return 0;
}