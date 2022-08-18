#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, id = 1;
int board[1001][1001];
pii vis[1001][1001];
int movement[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

void bfs(int x, int y) {
    queue<pii> q;
    q.push({x, y});
    vis[x][y].second = 1;

    int cnt = 1;
    vector<pii> ls;
    ls.push_back({x, y});

    while (!q.empty()) {
        int nx = q.front().first;
        int ny = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int tx = nx + movement[i][0];
            int ty = ny + movement[i][1];

            if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
            if (vis[tx][ty].second != 0 || board[tx][ty]) continue;

            vis[tx][ty].second = 1;
            q.push({tx, ty});
            ls.push_back({tx, ty});
            ++cnt;
        }
    }

    for (pii e : ls) {
        vis[e.first][e.second].first = id;
        vis[e.first][e.second].second = cnt;
    }
    ++id;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            board[i][j] = c - '0';
            vis[i][j] = {0, 0};
        }
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == 0 && !vis[i][j].second) {
                bfs(i, j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == 0) cout << "0";
            else {
                set<int> s;
                int ret = 1;
                for (int k = 0; k < 4; ++k) {
                    int xx = i + movement[k][0];
                    int yy = j + movement[k][1];

                    if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;

                    int cur_id = vis[xx][yy].first;
                    int cnt = vis[xx][yy].second;

                    if (s.find(cur_id) != s.end()) continue;
                    s.insert(cur_id);

                    ret += cnt;
                }
                cout << ret % 10;
            }
        }

        cout << "\n";
    }
    
    
    return 0;
}