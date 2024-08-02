#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

unordered_map<int, bool> um;
bool vis[5][5];
int asterisk_count = 0;
int movement[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

pii index2coord(int index) {
    return make_pair(index / 5, index % 5);
}

int coord2index(int row, int col) {
    return row * 5 + col;
}

bool is_connected(int status) {
    int x, y;
    memset(vis, false, sizeof(vis));

    // 시작 지점을 찾는다. (조각)
    for (int i = 0; i < 25; ++i)
        if (status & (1 << i)) {
            pii coord = index2coord(i);
            x = coord.first;
            y = coord.second;
            break;
        }

    // 조각으로 부터 연결된 다른 모든 조각의 개수를 센다.
    queue<pii> q;
    q.push({x, y});
    vis[x][y] = true;

    int count = 0;
    while (!q.empty()) {
        int nx = q.front().first;
        int ny = q.front().second;
        q.pop();

        ++count;

        for (int i = 0; i < 4; ++i) {
            int tx = nx + movement[i][0];
            int ty = ny + movement[i][1];

            if (tx < 0 || tx >= 5 || ty < 0 || ty >= 5) continue;
            if (vis[tx][ty]) continue;
            vis[tx][ty] = true;

            int index = coord2index(tx, ty);
            if (status & (1 << index)) {
                q.push({tx, ty});
            }
        }
    }

    return count == asterisk_count;
}

int solve(int status) {
    queue<pii> q;
    q.push({status, 0});
    um[status] = true;

    while (!q.empty()) {
        int now = q.front().first;
        int cnt = q.front().second;
        q.pop();

        if (is_connected(now)) return cnt;

        for (int i = 0; i < 25; ++i) {

            // 현재의 위치에 조각이 존재하는 경우
            if (now & (1 << i)) {

                // 조각의 위치를 index에서 좌표 형식으로 변환
                pii coord = index2coord(i);
                int x = coord.first;
                int y = coord.second;

                // 조각이 이동할 수 있는 경로: 상 / 하 / 좌 / 우
                for (int j = 0; j < 4; ++j) {
                    int nx = x + movement[j][0];
                    int ny = y + movement[j][1];

                    // 범위를 초과하는 경우
                    if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;

                    int new_status = now;
                    new_status = new_status ^ (1 << i);
                    new_status = new_status | (1 << coord2index(nx, ny));

                    // 이미 이전에 해당 상황을 처리했던 이력이 존재하는 경우
                    if (um[new_status] == true) continue;

                    // queue에 삽입하여 다음을 위한 준비.
                    um[new_status] = true;
                    q.push({new_status, cnt + 1});
                }
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 5 x 5 크기의 보드판은 int 형 변수 1개로 상태 표현이 가능하다. (비트마스킹)
    int status = 0;
    for (int i = 0; i < 25; ++i) {
        char c; cin >> c;
        if (c == '*') {
            ++asterisk_count;
            status |= (1 << i);
        }
    }

    // 초기 상태를 기준으로, 각 지점에 대해 상하좌우 움직일 수 있다면, 움직이도록 bfs를 통해 탐색한다.
    cout << solve(status) << "\n";
    
    return 0;
}