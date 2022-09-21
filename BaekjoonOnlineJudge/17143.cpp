#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct SHARK {
    int x, y;
    int speed;
    int direction;
    int size;
    bool is_alive = true;
};


int n, m, k;
int board[101][101];
int movement[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}};

vector<int> temp_board[101][101];
vector<SHARK> shark;


void move_shark() {

    // 상어 이동
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int now_shark_id = board[i][j];
            if (now_shark_id != -1 && shark[now_shark_id].is_alive) {
                SHARK &cur_shark = shark[now_shark_id];
                int move_cnt = cur_shark.speed;
                int &x = cur_shark.x;
                int &y = cur_shark.y;
                int &dir = cur_shark.direction;

                while (move_cnt--) {
                move:

                    int xx = x + movement[dir][0];
                    int yy = y + movement[dir][1];

                    // 방향 전환
                    if (xx < 0 || xx >= n || yy < 0 || yy >= m) {
                        if (dir <= 2) dir ^= (1 ^ 2);
                        else dir ^= (3 ^ 4);
                        goto move;
                    }

                    x = xx;
                    y = yy;
                }

                temp_board[x][y].push_back(now_shark_id);
            }
        }
    }

    // 한 칸에 상어가 여러마리 있는 경우 제거
    memset(board, -1, sizeof(board));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!temp_board[i][j].empty()) {
                sort(temp_board[i][j].begin(), temp_board[i][j].end(), [](const int &id1, const int &id2) -> bool {
                    return shark[id1].size > shark[id2].size;
                });
                board[i][j] = temp_board[i][j][0];

                for (int t = 1; t < temp_board[i][j].size(); ++t) {
                    int shark_id = temp_board[i][j][t];
                    shark[shark_id].is_alive = false;
                }
            }

            temp_board[i][j].clear();
        }
    }
}


int find_shark(int x) {
    for (int i = 0; i < n; ++i) {
        int shark_id = board[i][x];
        if (shark_id != -1 && shark[shark_id].is_alive) {
            shark[shark_id].is_alive = false;
            return shark[shark_id].size;
        }
    }

    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(board, -1, sizeof(board));

    cin >> n >> m >> k;

    shark.resize(k);

    int shark_id = 0;
    for (SHARK &e : shark) {
        cin >> e.x >> e.y >> e.speed >> e.direction >> e.size;
        if (e.direction <= 2) e.speed %= 2 * (n - 1);
        else e.speed %= 2 * (m - 1);
        
        --e.x; --e.y;
        e.is_alive = true;
        board[e.x][e.y] = shark_id++;
    }

    int cur_x = -1, answer = 0;
    while (cur_x++ < m) {
        // 상어중에서 땅과 제일 가까운 상어를 잡는다.
        answer += find_shark(cur_x);;

        // 상어가 이동한다.
        move_shark();
    }

    cout << answer << "\n";
    
    return 0;
}