#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

#define VERTICAL 0
#define HORIZONTAL 1
#define TREE '1'
using namespace std;

struct LOG {
    int center_x;
    int center_y;
    int direction;

    LOG(int x, int y, int d) : center_x(x), center_y(y), direction(d) {};

    bool operator == (LOG targ) {
        return center_x == targ.center_x && center_y == targ.center_y && direction == targ.direction;
    }
};

int n;
char board[51][51];
bool vis[51][51][2];

int cx = -1, cy = -1, cdir = -1;
int ex = -1, ey = -1, edir = -1;

bool can_rotate(int x, int y) {
    if (x <= 0 || y <= 0 || x >= n - 1 || y >= n -1) return false;

    for (int i = x - 1; i <= x + 1; ++i)
        for (int j = y - 1; j <= y + 1; ++j)
            if (board[i][j] == TREE)
                return false;

    return true;
}

bool can_move(int x, int y, int dir) {
    if (dir == HORIZONTAL) {
        if (board[x][y - 1] != TREE && board[x][y] != TREE && board[x][y + 1] != TREE) return true;
        else return false;
    }

    else {
        if (board[x - 1][y] != TREE && board[x][y] != TREE && board[x + 1][y] != TREE) return true;
        else return false;
    }
}
int bfs(int cx, int cy, int cdir) {

    memset(vis, false, sizeof(vis));

    queue<pair<LOG, int>> q;
    q.push({{cx, cy, cdir}, 0});
    vis[cx][cy][cdir] = true;

    while (!q.empty()) {
        LOG here = q.front().first;
        int x = here.center_x;
        int y = here.center_y;
        int d = here.direction;
        int mcnt = q.front().second;
        q.pop();

        if (here == LOG(ex, ey, edir)) return mcnt;

        // 상
        int up = x - (d == VERTICAL ? 2 : 1);
        if (up >= 0 && !vis[x - 1][y][d] && can_move(x - 1, y, d)) {
            vis[x - 1][y][d] = true;
            q.push({{x - 1, y, d}, mcnt + 1});
        }

        // 하
        int down = x + (d == VERTICAL ? 2 : 1);
        if (down < n && !vis[x + 1][y][d] && can_move(x + 1, y, d)) {
            vis[x + 1][y][d] = true;
            q.push({{x + 1, y, d}, mcnt + 1});
        }

        // 좌
        int left_most = y - (d == HORIZONTAL ? 2 : 1);
        if (left_most >= 0 && !vis[x][y - 1][d] && can_move(x, y - 1, d)) {
            vis[x][y - 1][d] = true;
            q.push({{x, y - 1, d}, mcnt + 1});
        }

        // 우
        int right_most = y + (d == HORIZONTAL ? 2 : 1);
        if (right_most < n && !vis[x][y + 1][d] && can_move(x, y + 1, d)) {
            vis[x][y + 1][d] = true;
            q.push({{x, y + 1, d}, mcnt + 1});
        }

        // 방향변경
        int new_dir = d ^ (HORIZONTAL ^ VERTICAL);
        if (can_rotate(x, y) && !vis[x][y][new_dir]) {
            vis[x][y][new_dir] = true;
            q.push({{x, y, new_dir}, mcnt + 1});
        }
    }

    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> board[i][j];


    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (board[i][j] == 'B' && cx == -1) {
                if (j + 1 < n && board[i][j + 1] == 'B') {
                    cx = i; cy = j + 1; cdir = HORIZONTAL;
                } else {
                    cx = i + 1; cy = j; cdir = VERTICAL;
                }
            }

            else if (board[i][j] == 'E' && ex == -1) {
                if (j + 1 < n && board[i][j + 1] == 'E') {
                    ex = i; ey = j + 1; edir = HORIZONTAL;
                } else {
                    ex = i + 1; ey = j; edir = VERTICAL;
                }
            }


    cout << bfs(cx, cy, cdir) << "\n";

    return 0;
}