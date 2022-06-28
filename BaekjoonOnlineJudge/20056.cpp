#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 51

using namespace std;

struct FIREBALL {
    int r; // 행
    int c; // 열
    int m; // 질량
    int s; // 속도
    int d; // 방향
};

int n, m, k; // 격자판의 크기 (n x n), 파이어볼의 수(m), 명령의 수(k)
int movement[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
queue<FIREBALL> board[MAX][MAX];

bool check_dir(vector<FIREBALL> &fireballs) {
    int result = fireballs[0].d % 2;
    for (auto fireball : fireballs) {
        if (fireball.d % 2 != result) return false;
    }
    return true;
}

void move_balls() {

    int move_ball_cnt = 0;
    int board_queue_size[MAX][MAX];
    memset(board_queue_size, 0, sizeof(board_queue_size));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            board_queue_size[i][j] = (int)board[i][j].size();

    // 모든 파이어볼 이동
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            while (board_queue_size[i][j]--) {
                FIREBALL f = board[i][j].front(); board[i][j].pop();
                ++move_ball_cnt;
                int nx = f.r + movement[f.d][0] * f.s;
                int ny = f.c + movement[f.d][1] * f.s;

                while (nx < 1) nx += n;
                while (ny < 1) ny += n;
                while (n < nx) nx -= n;
                while (n < ny) ny -= n;

                board[nx][ny].push({nx, ny, f.m, f.s, f.d});
            }
        }
    }


    // 파이어볼 합치기
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {

            // 현재 칸에 파이어볼이 2개 이상인 경우 -> 합치기
            if (board[i][j].size() >= 2) {
                vector<FIREBALL> fireballs;
                fireballs.clear();

                while (!board[i][j].empty()) {
                    FIREBALL fireball = board[i][j].front();
                    board[i][j].pop();
                    fireballs.push_back(fireball);
                }

                int total_m = 0, total_s = 0;
                for (auto fireball : fireballs) {
                    total_m += fireball.m;
                    total_s += fireball.s;
                }

                int new_m = total_m / 5;
                int new_s = total_s / (int)fireballs.size();
                if (new_m == 0) continue;

                bool is_dir_same = check_dir(fireballs);
                if (is_dir_same) {
                    board[i][j].push({i, j, new_m, new_s, 0});
                    board[i][j].push({i, j, new_m, new_s, 2});
                    board[i][j].push({i, j, new_m, new_s, 4});
                    board[i][j].push({i, j, new_m, new_s, 6});
                } else {
                    board[i][j].push({i, j, new_m, new_s, 1});
                    board[i][j].push({i, j, new_m, new_s, 3});
                    board[i][j].push({i, j, new_m, new_s, 5});
                    board[i][j].push({i, j, new_m, new_s, 7});
                }

            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 입력
    cin >> n >> m >> k;

    while (m--) {
        FIREBALL fireball;
        cin >> fireball.r >> fireball.c >> fireball.m >> fireball.s >> fireball.d;
        board[fireball.r][fireball.c].push(fireball);
    }

    // 이동
    while (k--) move_balls();

    int answer = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            while (!board[i][j].empty()) {
                answer += board[i][j].front().m;
                board[i][j].pop();
            }

    cout << answer << "\n";


    return 0;
}