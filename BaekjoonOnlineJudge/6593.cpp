#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int L, R, C;
char board[31][31][31];

int movement[6][3] = {{0, 0, 1}, {0, 1, 0}, {0, -1, 0}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}};
bool vis[31][31][31];
int sx, sy, sz;

struct Q {
    int x;
    int y;
    int z;
    int t;
};

int bfs(int x, int y, int z) {
    queue<Q> q;
    q.push({x, y, z, 0});
    vis[x][y][z] = true;

    while (!q.empty()) {
        int here_x = q.front().x;
        int here_y = q.front().y;
        int here_z = q.front().z;
        int here_t = q.front().t;
        q.pop();

        if (board[here_x][here_y][here_z] == 'E') {
            return here_t;
        }

        for (int i = 0; i < 6; ++i) {
            int there_x = here_x + movement[i][0];
            int there_y = here_y + movement[i][1];
            int there_z = here_z + movement[i][2];

            if (there_x < 0 || there_x >= R || there_y < 0 || there_y >= C || there_z < 0 || there_z >= L) continue;
            if (vis[there_x][there_y][there_z] || board[there_x][there_y][there_z] == '#') continue;

            vis[there_x][there_y][there_z] = true;
            q.push({there_x, there_y, there_z, here_t + 1});
        }
    }

    return -1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    while (true) {
        cin >> L >> R >> C;
        if (L == 0 && R == 0 && C == 0) break;

        memset(vis, false, sizeof(vis));

        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < R; ++j) {
                for (int k = 0; k < C; ++k) {
                    cin >> board[j][k][i];
                    if (board[j][k][i] == 'S') {
                        sx = j;
                        sy = k;
                        sz = i;
                    }
                }
            }
        }

        int ret = bfs(sx, sy, sz);
        if (ret == -1) cout << "Trapped!\n";
        else cout << "Escaped in " << ret << " minute(s).\n";
    }

    return 0;
}