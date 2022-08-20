#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int board[1001][1001];
pii cnt[1001][1001];
bool vis[1001][1001];
int id = 1;

int movement[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void bfs(int x, int y) {
    queue<pii> q;
    q.push({x, y});
    vis[x][y] = true;

    vector<pii> coords;
    coords.push_back({x, y});
    
    int ret = 1;

    while (!q.empty()) {
        int here_x = q.front().first;
        int here_y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int there_x = here_x + movement[i][0];
            int there_y = here_y + movement[i][1];

            if (there_x < 0 || there_x >= n || there_y < 0 || there_y >= m) continue;
            if (vis[there_x][there_y] || board[there_x][there_y] == 0) continue;

            ++ret;
            vis[there_x][there_y] = true;
            q.push({there_x, there_y});
            coords.push_back({there_x, there_y});
        }
    }

    for (pii c : coords) {
        cnt[c.first][c.second].first = ret;
        cnt[c.first][c.second].second = id;
    }
    ++id;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(vis, false, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));

    cin >> n >> m;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> board[i][j];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] && !vis[i][j]) {
                bfs(i, j);
            }
        }
    }    

    int answer = 0;
    
    set<int> s;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] == 0) {
                int ret = 1;
                s.clear();

                for (int k = 0; k < 4; ++k) {
                    int ti = i + movement[k][0];
                    int tj = j + movement[k][1];

                    if (ti < 0 || ti >= n || tj < 0 || tj >= m || !board[ti][tj]) continue;

                    int value = cnt[ti][tj].first;
                    int cur_id = cnt[ti][tj].second;

                    if (s.find(cur_id) != s.end()) continue;
                    s.insert(cur_id);

                    ret += value;
                }
                answer = max(answer, ret);
            }   

    cout << answer << "\n";
    return 0;
}