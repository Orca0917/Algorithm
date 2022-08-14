#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct PERSON {
    int x;
    int y;
    int move_cnt;
};

struct FIRE {
    int x;
    int y;
};

int n, m; 
char board[1001][1001];
bool vis[1001][1001];
bool fire_vis[1001][1001];
int movement[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
queue<FIRE> fire_q;

void spread_fire() {
    int q_size = (int)fire_q.size();

    while (q_size--) {
        int here_x = fire_q.front().x;
        int here_y = fire_q.front().y;
        fire_q.pop();

        for (int i = 0; i < 4; ++i) {
            int there_x = here_x + movement[i][0];
            int there_y = here_y + movement[i][1];

            if (there_x < 0 || there_x >= n || there_y < 0 || there_y >= m) continue;
            if (board[there_x][there_y] == '#' || board[there_x][there_y] == 'F') continue;
            if (fire_vis[there_x][there_y]) continue;
            

            fire_vis[there_x][there_y] = true;
            board[there_x][there_y] = 'F';
            fire_q.push({there_x, there_y});
        }
    }
}

int bfs(int sx, int sy) {
    queue<PERSON> q;

    q.push({sx, sy, 1});
    vis[sx][sy] = true;

    int prev_cnt = 0;

    while (!q.empty()) {

        int here_x = q.front().x;
        int here_y = q.front().y;
        int here_cnt = q.front().move_cnt;
        q.pop();

        if (here_cnt != prev_cnt) {
            prev_cnt = here_cnt;
            spread_fire();
        }

        if (here_x == 0 || here_x == n - 1 || here_y == 0 || here_y == m - 1) return here_cnt;

        for (int i = 0; i < 4; ++i) {
            int there_x = here_x + movement[i][0];
            int there_y = here_y + movement[i][1];

            if (there_x < 0 || there_x >= n || there_y < 0 || there_y >= m) continue;
            if (board[there_x][there_y] == '#' || board[there_x][there_y] == 'F') continue;
            if (vis[there_x][there_y]) continue;

            vis[there_x][there_y] = true;
            q.push({there_x, there_y, here_cnt + 1});
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    int start_x, start_y;

    memset(vis, false, sizeof(vis));
    memset(fire_vis, false, sizeof(fire_vis));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 'J') {
                start_x = i;
                start_y = j;
            } else if (board[i][j] == 'F') {
                fire_q.push({i, j});
                fire_vis[i][j] = true;
            }
        }
    }


    int result = bfs(start_x, start_y);

    if (result == -1) cout << "IMPOSSIBLE\n";
    else cout << result << "\n";

    return 0;
}