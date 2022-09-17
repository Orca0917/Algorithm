#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int board[51][51];
bool prev_cloud[51][51];

int movement[9][2] = {{0, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> board[i][j];


    queue<pii> cloud;
    cloud.push({n, 1});
    cloud.push({n, 2});
    cloud.push({n - 1, 1});
    cloud.push({n - 1, 2});


    while (m--) {
        int dir, move; cin >> dir >> move;

        memset(prev_cloud, false, sizeof(prev_cloud));

        // 1. 구름의 이동
        int q_size = (int)cloud.size();
        while (q_size--) {
            int x = cloud.front().first;
            int y = cloud.front().second;
            cloud.pop();

            int xx = x + movement[dir][0] * move;
            int yy = y + movement[dir][1] * move;

            while (xx < 1) xx += n;
            while (yy < 1) yy += n;

            while (xx > n) xx -= n;
            while (yy > n) yy -= n;
            
            board[xx][yy] += 1;
            cloud.push({xx, yy});
            prev_cloud[xx][yy] = true;
        }

        // 2. 물 복제
        while (!cloud.empty()) {
            int x = cloud.front().first;
            int y = cloud.front().second;
            cloud.pop();

            for (int i = 2; i < 9; i += 2) {
                int xx = x + movement[i][0];
                int yy = y + movement[i][1];

                if (xx <= 0 || xx > n || yy <= 0 || yy > n) continue;
                if (board[xx][yy] != 0) board[x][y] += 1;
            }
        }

        // 3. 구름 생성
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (board[i][j] >= 2 && !prev_cloud[i][j]) {
                    cloud.push({i, j});
                    board[i][j] -= 2;
                }
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            answer += board[i][j];
        }
    }

    cout << answer << "\n";
    
    
    return 0;
}