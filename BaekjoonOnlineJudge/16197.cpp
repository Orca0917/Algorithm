#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

#define x first
#define y second

using namespace std;

int n, m;
char board[20][20];
bool vis[21][21][21][21];
int movement[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

struct Data {
    int x1, y1, x2, y2;
    int cnt = 0;
};

int fall_count(int x1, int y1, int x2, int y2) {
    int cnt = 0;

    if (x1 < 0 || y1 < 0 || x1 == n || y1 == m) ++cnt;
    if (x2 < 0 || y2 < 0 || x2 == n || y2 == m) ++cnt;

    return cnt;
}

int solve(int x1, int y1, int x2, int y2) {

    memset(vis, false, sizeof(vis));
    vis[x1][y1][x2][y2] = true;
    
    queue<Data> q;
    q.push({x1, y1, x2, y2, 0});

    while (!q.empty()) {
        Data now = q.front(); q.pop();

        // cout << now.x1 << now.y1 << now.x2 << now.y2 << "\n";

        if (now.cnt == 10) return -1;

        for (int i = 0; i < 4; ++i) {
            int nx1 = now.x1 + movement[i][0];
            int ny1 = now.y1 + movement[i][1];
            if (nx1 >= 0 && nx1 < n && ny1 >= 0 && ny1 < m && board[nx1][ny1] == '#') nx1 = now.x1, ny1 = now.y1;

            int nx2 = now.x2 + movement[i][0];
            int ny2 = now.y2 + movement[i][1];
            if (nx2 >= 0 && nx2 < n && ny2 >= 0 && ny2 < m && board[nx2][ny2] == '#') nx2 = now.x2, ny2 = now.y2;

            // 하나만 떨어지는 경우
            // cout << nx1 << ny1 << nx2 << ny2 << " -> " << fall_count(nx1, ny1, nx2, ny2) << "\n";
            if (fall_count(nx1, ny1, nx2, ny2) == 1) return now.cnt + 1;

            // 둘 다 떨어지는 경우
            if (fall_count(nx1, ny1, nx2, ny2) == 2) continue;

            if (vis[nx1][ny1][nx2][ny2]) continue;
            vis[nx1][ny1][nx2][ny2] = true;
            q.push({nx1, ny1, nx2, ny2, now.cnt + 1});
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    vector<pii> v;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 'o') v.push_back({i, j});
        }
    }

    cout << solve(v[0].first, v[0].second, v[1].first, v[1].second);
    
    return 0;
}