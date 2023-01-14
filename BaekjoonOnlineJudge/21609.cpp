#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Group {
    int size = 0;
    int rainbow = 0;
    int row = -1;
    int col = -1;
};

int movement[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
bool vis[21][21];
int board[21][21];
int n, m;
vector<pii> rainbow_pos;

Group bfs(int x, int y, int color, int setter) {
    queue<pii> q;
    q.push({x, y});
    vis[x][y] = true;

    vector<pii> grp;
    grp.push_back({x, y});
    int rainbow_cnt = 0;

    while (!q.empty()) {
        tie(x, y) = q.front(); q.pop();

        for (int i = 0; i < 4; ++i) {
            int xx = x + movement[i][0];
            int yy = y + movement[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
            if (board[xx][yy] != color && board[xx][yy] != 0) continue;
            if (vis[xx][yy]) continue;

            q.push({xx, yy});
            grp.push_back({xx, yy});
            vis[xx][yy] = true;
            if (board[xx][yy] == 0) {
                rainbow_pos.push_back({xx, yy});
                rainbow_cnt += 1;
            }
        }
    }
    
    for (pii e : rainbow_pos) vis[e.first][e.second] = false;

    Group ret;
    if (setter != -1) {
        for (pii e : grp) {
            board[e.first][e.second] = -2;
        }
        return ret;
    }

    sort (grp.begin(), grp.end());
    
    ret.size = grp.size();
    if (ret.size == 0) return ret;

    ret.rainbow = rainbow_cnt;

    for (pii e : grp) {
        if (board[e.first][e.second] > 0) {
            ret.row = e.first;
            ret.col = e.second;
            break;
        }
    }

    return ret;
}


void gravity_fall() {
    for (int j = 0; j < n; ++j) {
        for (int i = n - 1; i >= 0; --i) {
            if (board[i][j] == -2) {
                int k = i;
                while (k >= 0) {
                    if (board[--k][j] != -2) break;
                }
                if (board[k][j] == -1 || k < 0) continue;
                board[i][j] = board[k][j];
                board[k][j] = -2;
            }
        }
    }
}


void rotate_rev90() {
    for (int i = 0; i < n / 2; ++i) {
        for (int j = i; j < n - i - 1; ++j) {
            int temp = board[i][j];
            board[i][j] = board[j][n - 1 - i];
            board[j][n - 1 - i] = board[n - 1 - i][n - 1 - j];
            board[n - 1 - i][n - 1 - j] = board[n - 1 - j][i];
            board[n - 1 - j][i] = temp;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> board[i][j];

    int answer = 0;

    while (true) {
        
        Group biggest;
        memset(vis, false, sizeof(vis));

        // 1. 블록 그룹 찾기
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (vis[i][j]) continue;
                if (board[i][j] > 0 && !vis[i][j]) {
                    Group ret = bfs(i, j, board[i][j], -1);
                    if (ret.size > biggest.size) biggest = ret;
                    else if (ret.size == biggest.size) {
                        if (ret.rainbow > biggest.rainbow) biggest = ret;
                        else if (ret.rainbow == biggest.rainbow) {
                            if (ret.row > biggest.row) biggest = ret;
                            else if (ret.row == biggest.row) {
                                if (ret.col > biggest.col) biggest = ret;
                            }
                        }
                    }
                }
            }

        memset(vis, false, sizeof(vis));

        if (biggest.size < 2) break;

        // 2. 블록 제거
        bfs(biggest.row, biggest.col, board[biggest.row][biggest.col], 1);
        answer += biggest.size * biggest.size;

        // 3. 중력 작용
        gravity_fall();

        // 4. 반시계 90
        rotate_rev90();

        // 5. 중력 작용
        gravity_fall();
    }

    cout << answer << "\n";
    
    return 0;
}