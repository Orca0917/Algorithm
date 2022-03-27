#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int bee_time[801][801];
int bear_time[801][801];
char grid[801][801]; // 그리드 정보
pii start, dest; // 곰돌이의 출발지, 도착지

queue<tuple<int, int, int>> bees; // 벌집의 위치

void spread_bees() {
    int x, y, c;
    while (!bees.empty()) {
        tie(x, y, c) = bees.front(); bees.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + "0112"[i] - '0' - 1;
            int ny = y + "1201"[i] - '0' - 1;
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if ((grid[nx][ny] != 'G' && grid[nx][ny] != 'M') || bee_time[nx][ny] != -1) continue;
            bee_time[nx][ny] = c + 1;
            bees.push({nx, ny, c + 1});
        }
    }
}

bool can_go_home(int eat_time) {
    memset(bear_time, -1, sizeof(bear_time));

    queue<tuple<int, int, int>> q;
    q.push({start.first, start.second, 0});
    bear_time[start.first][start.second] = 0;

    if (eat_time >= bee_time[start.first][start.second]) return false;

    int now_x, now_y, now_time;

    while (!q.empty()) {
        tie(now_x, now_y, now_time) = q.front(); 
        q.pop();

        

        for (int i = 0; i < 4; ++i) {
            int there_x = now_x + "0112"[i] - '0' - 1;
            int there_y = now_y + "1201"[i] - '0' - 1;

            if (make_pair(there_x, there_y) == dest) return true;

            // 그리드 밖으로 벗어나는 경우
            if (there_x < 0 || there_x >= n || there_y < 0 || there_y >= n) continue;

            // 이미 이동했거나, 갈 수 없는 곳인 경우 (벌집, 나무)
            if (bear_time[there_x][there_y] != -1 || grid[there_x][there_y] == 'H' || grid[there_x][there_y] == 'T') continue;

            // 벌들에게 먹히는 경우
            if (eat_time + (now_time + 1) / m >= bee_time[there_x][there_y] && bee_time[there_x][there_y] != -1) continue;
            bear_time[there_x][there_y] = now_time + 1;
            q.push({there_x, there_y, now_time + 1});
        }
    }

    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(bee_time, -1, sizeof(bee_time));

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'M')
                start = {i, j};
            else if (grid[i][j] == 'D')
                dest = {i, j};
            else if (grid[i][j] == 'H') {
                bee_time[i][j] = 0;
                bees.push({i, j, 0});
            }
        }

    spread_bees();

    int lo = 0, hi = 1e7, answer = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (can_go_home(mid)) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << answer << "\n";

    return 0;
}