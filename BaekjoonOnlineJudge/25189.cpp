#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1001

using namespace std;

struct q_type {
    int x;
    int y;
    int skip_cnt;
    int move_cnt;
};

int N; // # of rows
int M; // # of cols

pii frog_pos;
pii home_pos;

int board[MAX][MAX];
bool vis[MAX][MAX][2];
bool skip_row[MAX], skip_col[MAX];

int bfs(pii frog_pos) {

    // init visit stat.
    memset(vis, false, sizeof(vis));
    memset(skip_row, false, sizeof(skip_row));
    memset(skip_col, false, sizeof(skip_col));

    queue<q_type> q;
    q.push({frog_pos.first, frog_pos.second, 0, 0});
    vis[frog_pos.first][frog_pos.second][0] = true;

    while (!q.empty()) {
        int here_x = q.front().x;
        int here_y = q.front().y;
        int here_skip = q.front().skip_cnt;
        int here_move = q.front().move_cnt;
        q.pop();

        if (here_x == home_pos.first && here_y == home_pos.second) {
            return here_move;
        }

        // 1. 개구리밥 무시
        if (here_skip == 0) {
            // left, right
            if (skip_row[here_x] == false) {
                skip_row[here_x] = true;
                for (int i = 1; i <= M; ++i) {
                    if (vis[here_x][i][1]) continue;
                    vis[here_x][i][1] = true;
                    q.push({here_x, i, 1, here_move + 1});
                }
            }

            // Up, down
            if (skip_col[here_y] == false) {
                skip_col[here_y] = true;
                for (int i = 1; i <= N; ++i) {
                    if (vis[i][here_y][1]) continue;
                    vis[i][here_y][1] = true;
                    q.push({i, here_y, 1, here_move + 1});
                }
            }
        }

        // 2. 개구리밥 사용
        for (int i = 0; i < 4; ++i) {
            int jump = board[here_x][here_y];
            int there_x = here_x + jump * (("0121"[i] - '0') - 1);
            int there_y = here_y + jump * (("1210"[i] - '0') - 1);

            // out of range
            if (there_x < 1 || there_x > N || there_y < 1 || there_y > M) continue;
            if (vis[there_x][there_y][here_skip]) continue;
            vis[there_x][there_y][here_skip] = true;
            q.push({there_x, there_y, here_skip, here_move + 1});
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    cin >> frog_pos.first >> frog_pos.second;
    cin >> home_pos.first >> home_pos.second;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> board[i][j];
        }
    }

    int result = bfs(frog_pos);
    cout << result << "\n";

    return 0;
}