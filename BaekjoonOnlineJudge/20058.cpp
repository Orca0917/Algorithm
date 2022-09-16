#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, q;
int movement[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int board[65][65];
int temp_board[65][65];
bool vis[65][65];

void print_board() {
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << board[i][j] << " \n"[j == n -1];
        }
    }
}

void copy_board() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = temp_board[i][j];
        }
    }
    memset(temp_board, 0, sizeof(temp_board));
}

void rotate_line(int x, int y, int sz) {
    for (int i = 0; i < sz; ++i) temp_board[x + i][y + sz - 1] = board[x][y + i];
    for (int i = 0; i < sz; ++i) temp_board[x + sz - 1][y + sz - 1 - i] = board[x + i][y + sz - 1];
    for (int i = 0; i < sz; ++i) temp_board[x + sz - 1 - i][y] = board[x + sz - 1][y + sz - 1 - i];
    for (int i = 0; i < sz; ++i) temp_board[x][y + i] = board[x + sz - 1 - i][y];
}

void rotate_board(int sx, int sy, int width) {
    int sz = width;
    for (int i = 0; sz != 0; ++i) {
        rotate_line(sx + i, sy + i, sz);
        sz -= 2;
    }
}


int bfs(int x, int y) {
    queue<pii> q;
    q.push({x, y});
    vis[x][y] = true;

    int ret = 0;

    while (!q.empty()) {
        int nx = q.front().first;
        int ny = q.front().second;
        ++ret;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int xx = nx + movement[i][0];
            int yy = ny + movement[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
            if (vis[xx][yy] || board[xx][yy] == 0) continue;

            vis[xx][yy] = true;
            q.push({xx, yy});
        }
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> q;

    n = 1 << n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> board[i][j];

    while (q--) {
        int width; cin >> width;
        width = 1 << width;

        // 격자판 돌리기
        for (int i = 0; i < n && width != 1; i += width) {
            for (int j = 0; j < n; j += width) {
                rotate_board(i, j, width);
            }
        }

        if (width != 1) copy_board();

        // 붙어있는 칸이 3개 미만 -> 삭제
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                temp_board[i][j] = board[i][j];
                if (temp_board[i][j] == 0) continue;

                int adj_ice = 0;
                for (int mv = 0; mv < 4; ++mv) {
                    int x = i + movement[mv][0];
                    int y = j + movement[mv][1];

                    if (x < 0 || x >= n || y < 0 || y >= n) continue;
                    if (board[x][y] > 0) adj_ice += 1;
                }

                if (adj_ice < 3) temp_board[i][j] -= 1;
            } 
        }
    
        copy_board();
    }

    // print_board();
    
    int answer = 0, total = 0;
    memset(vis, false, sizeof(vis));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            total += board[i][j];

            if (board[i][j] > 0 && !vis[i][j]) {
                int ret = bfs(i, j);
                answer = max(answer, ret);
            }
        }
    }
    
    cout << total << "\n" << answer << "\n";

    return 0;
}