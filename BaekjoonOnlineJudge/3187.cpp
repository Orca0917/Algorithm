#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
char board[251][251];
bool vis[251][251];
int movement[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int wolf = 0, sheep = 0;
void bfs(int x, int y) {
    queue<pii> q;
    q.push({x, y});
    vis[x][y] = true;

    int w = (int)(board[x][y] == 'v');
    int s = (int)(board[x][y] == 'k');

    while (!q.empty()) {
        int here_x = q.front().first;
        int here_y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int there_x = here_x + movement[i][0];
            int there_y = here_y + movement[i][1];

            if (there_x < 0 || there_x >= n || there_y < 0 || there_y >= m) continue;
            if (vis[there_x][there_y] || board[there_x][there_y] == '#') continue;

            vis[there_x][there_y] = true;
            if (board[there_x][there_y] == 'v') ++w;
            else if (board[there_x][there_y] == 'k') ++s;
            q.push({there_x, there_y});
        }
    }

    if (w < s) sheep += s;
    else wolf += w;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];
    }

    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (board[i][j] != '#' && vis[i][j] == false) {
                bfs(i, j);
            }
        }
    
    cout << sheep << " " << wolf << "\n";

    return 0;
}