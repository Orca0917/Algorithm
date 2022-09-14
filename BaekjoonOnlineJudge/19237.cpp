#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

struct SHARK {
    int priority[5][4];
    int dir;
    bool is_alive = true;
};

struct SMELL {
    int shark_id = 0;
    int expire;
};

int n, m, k;
int board[21][21];
int movement[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

SHARK shark[401];
SMELL smell[21][21];
vector<pii> shark_pos(401);
vector<int> candidates[21][21];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 세로, 가로, 향기 지속시간
    cin >> n >> m >> k;
    
    // 격자의 상태 입력으로 받기
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int &cell = board[i][j];
            cin >> cell;

            if (cell != 0) {
                shark_pos[cell] = {i, j};
                smell[i][j] = {cell, k};
            }
        }
    }

    // 초기 상어가 바라보고 있는 방향
    for (int i = 1; i <= m; ++i) cin >> shark[i].dir;

    // 상어마다 방향별 다음 진행방향 우선순위 부여
    for (int shark_idx = 1; shark_idx <= m; ++shark_idx) {
        for (int dir = UP; dir <= RIGHT; ++dir) {
            for (int i = 0; i < 4; ++i) {
                cin >> shark[shark_idx].priority[dir][i];       
            }
        }
    }

    // 시뮬레이션 시작
    int left_shark = m;
    int time = 0;
    
    while (time++ < 1000 && left_shark > 1) {

        // 각 상어를 이동
        for (int id = 1; id <= m; ++id) {
            // 이미 죽은 상어 : pass
            if (!shark[id].is_alive) continue;

            // 현재 상어의 위치 + 어떤 상어(id)
            int x = shark_pos[id].first;
            int y = shark_pos[id].second;

            // 이동할 지역 탐색 시작
            int dir = shark[id].dir;
            pii next_move = {-1, -1};


            // CASE 1. 주변에 새로운 지역으로 이동
            for (int prior = 0; prior < 4; ++prior) {
                int next_dir = shark[id].priority[dir][prior];  // 다음 방향
                int next_x = x + movement[next_dir][0];         // 다음 x
                int next_y = y + movement[next_dir][1];         // 다음 y

                // 격자 밖으로 벗어나 이동 불가
                if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= n) continue;
                
                if (smell[next_x][next_y].expire == 0) {
                    next_move = {next_x, next_y};
                    shark[id].dir = next_dir;
                    break;
                }
            }

            if (next_move.first != -1) {
                candidates[next_move.first][next_move.second].push_back(id);
                continue;
            }


            // CASE 2. 이미 왔던 지역으로 다시 돌아가기
            for (int prior = 0; prior < 4; ++prior) {
                int next_dir = shark[id].priority[dir][prior];  // 다음 방향
                int next_x = x + movement[next_dir][0];         // 다음 x
                int next_y = y + movement[next_dir][1];         // 다음 y

                // 격자 밖으로 벗어나 이동 불가
                if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= n) continue;
                
                if (smell[next_x][next_y].shark_id == id) {
                    next_move = {next_x, next_y};
                    shark[id].dir = next_dir;
                    break;
                }
            }
            
            if (next_move.first != -1) {
                candidates[next_move.first][next_move.second].push_back(id);
                continue;
            }
        }

        memset(board, 0, sizeof(board));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (smell[i][j].expire > 0) --smell[i][j].expire;

                vector<int> &cell = candidates[i][j];
                if (cell.empty()) continue;

                sort(cell.begin(), cell.end());
                int winner = cell[0];

                board[i][j] = winner;
                smell[i][j] = {winner, k};
                shark_pos[winner] = {i, j};

                if (cell.size() >= 2) {
                    for (int t = 1; t < cell.size(); ++t) {
                        int dead_id = cell[t];
                        shark[dead_id].is_alive = false;
                        --left_shark;
                    }
                }

                cell.clear();
            }
        }
    }

    cout << (left_shark == 1 ? time - 1 : -1) << "\n";

    return 0;
}