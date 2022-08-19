#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int board[1001][1001];
queue<pii> q;

int movement[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

int bfs() {
    int q_size = (int)q.size();
    int ret = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 8; ++i) {
            int xx = x + movement[i][0];
            int yy = y + movement[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
            if (board[xx][yy] == 0) continue;

            board[xx][yy] -= 1;

            if (board[xx][yy] == 0) {
                q.push({xx, yy});
            }
        }

        if (--q_size == 0) {
            q_size = (int)q.size();
            ++ret;
        }
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    memset(board, 0, sizeof(board));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            if (c == '.') {
                board[i][j] = 0;
                q.push({i, j});
            }
            else board[i][j] = c - '0';
        }
    }

    cout << bfs() - 1 << "\n";

    return 0;
}