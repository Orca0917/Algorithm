#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int n, m;
int board[1001][1001];
bool visited[1001][1001];
int mv[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

int bfs(int x, int y) {
    queue<pii> q;
    q.push({x, y});
    visited[x][y] = true;

    int ret = 0;
    while (!q.empty()) {
        int nowX = q.front().first;
        int nowY = q.front().second;
        q.pop();

        ++ret;

        for (int i = 0; i < 4; ++i) {
            if ((board[nowX][nowY] & (1 << i)) == 0) {
                int tx = nowX + mv[i][0];
                int ty = nowY + mv[i][1];
                if (visited[tx][ty]) continue;
                visited[tx][ty] = true;
                q.push({tx, ty});
            }
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    vector<int> answer;
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!visited[i][j]) {
                answer.push_back(bfs(i, j));
            }

    sort(answer.rbegin(), answer.rend());
    for (auto e : answer) cout << e << " ";
    return 0;
}