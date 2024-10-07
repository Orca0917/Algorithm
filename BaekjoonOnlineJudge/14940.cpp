#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

int n, m;
int board[1001][1001];
int dist[1001][1001];

int mv[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

using namespace std;

void bfs(pii src) {

    // 방문 정보 초기화
    memset(dist, -1, sizeof(dist));

    // BFS를 위한 큐 선언 자료형 (좌표, 이동거리)
    queue<pair<pii, int>> q;
    q.push({src, 0});
    dist[src.first][src.second] = 0;

    while (!q.empty()) {
        // queue의 최하단 정보 선택
        int x = q.front().first.first;
        int y = q.front().first.second;
        int c = q.front().second;
        q.pop();

        // 상하좌우 인접한 공간 탐색
        for (int i = 0; i < 4; ++i) {
            int nx = x + mv[i][0];
            int ny = y + mv[i][1];

            // 경계선을 넘어가는 경우 확인
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            
            // 갈 수 없는 지형이거나 이미 방문했던 곳은 pass
            if (dist[nx][ny] != -1 || board[nx][ny] == 0) continue;

            q.push({{nx, ny}, c + 1});
            dist[nx][ny] = c + 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    
    pii src;
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 2)
                src = {i, j};
        }

    bfs(src);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            // 갈 수 없는 땅은 0, 원래 갈 수 있는데 막혀서 못가면 -1 출력
            cout << dist[i][j] * board[i][j] << " \n"[j == m - 1];
    
    return 0;
}