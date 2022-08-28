#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

int n, m;

struct Q {
    int x;
    int y;
    int dir;
    int cnt;
};

pii start = {-1, -1}, dest;
char board[101][101];
int vis[101][101][4];

int adj[4][3] = {{UP, LEFT, RIGHT}, {UP, RIGHT, DOWN}, {RIGHT, DOWN, LEFT}, {UP, LEFT, DOWN}};
int movement[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int bfs() {

    memset(vis, -1, sizeof(vis));

    queue<Q> q;

    for (int i = 0; i < 4; ++i ) {
        q.push({start.first, start.second, i, 0});
        vis[start.first][start.second][i] = true;
    }

    int dist = -1;
    int ret = 1e9;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int dir = q.front().dir;
        int cnt = q.front().cnt;
        q.pop();

        if (x == dest.first && y == dest.second) {
            ret = min(ret, cnt);
            continue;
        }

        for (int i = 0; i < 3; ++i) {
            int new_dir = adj[dir][i];
            int nx = x + movement[dir][0];
            int ny = y + movement[dir][1];

            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (board[nx][ny] == '*') continue;

            if (dir != new_dir) {
                if (vis[nx][ny][new_dir] != -1 && vis[nx][ny][new_dir] <= cnt + 1) continue;
                q.push({nx, ny, new_dir, cnt + 1});
                vis[nx][ny][new_dir] = cnt + 1;
            } else {
                if (vis[nx][ny][new_dir] != -1 && vis[nx][ny][new_dir] <= cnt) continue;
                q.push({nx, ny, new_dir, cnt});
                vis[nx][ny][new_dir] = cnt;;
            }
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char &c = board[i][j];
            cin >> c;

            if (c == 'C') {
                if (start.first == -1) { start = {i, j}; }
                else dest = {i, j};
            }
        }
    }
    
    cout << bfs() << "\n";

    return 0;
}