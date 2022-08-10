#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct CELL {
    int direction;
    int point;
    bool has_fish = true;
};

int answer = 0;
int movement[9][2] = {
    {0, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}
};

pii find_index(vector<vector<CELL>> stat, int value) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (stat[i][j].point == value) {
                if (stat[i][j].has_fish == true) return {i, j};
                else return {-1, -1};
            }

    return {-1, -1};
}

void backtrack(int x, int y, int score, vector<vector<CELL>> stat) {
    // 상어가 [x][y]에 있는 물고기를 먹는다.
    score += stat[x][y].point;
    answer = max(answer, score);
    stat[x][y].has_fish = false;
    int dir = stat[x][y].direction;

    // 남은 물고기들이 방향에 따라서 이동한다.
    int index = 1;
    while (index <= 16) {
        pii idx = find_index(stat, index++);
        if (idx.first == -1 && idx.second == -1) continue;

        int &fish_dir = stat[idx.first][idx.second].direction;
        for (int i = 0; i < 8; ++i) {
            if (fish_dir == 9) fish_dir = 1;
            int next_x = idx.first + movement[fish_dir][0];
            int next_y = idx.second + movement[fish_dir][1];
            
            if (next_x < 0 || next_y < 0 || next_x >= 4 || next_y >= 4) ++fish_dir;
            else if (next_x == x && next_y == y) ++fish_dir;
            else {
                swap(stat[idx.first][idx.second], stat[next_x][next_y]);
                break;
            }
        }
    }

    // 상어가 다음에 먹을 물고기를 찾는다.
    for (int i = 1; ; ++i) {
        int nx = x + i * movement[dir][0];
        int ny = y + i * movement[dir][1];

        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) break;
        if (stat[nx][ny].has_fish == false) continue;

        backtrack(nx, ny, score, stat);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<vector<CELL>> board(4, vector<CELL>(4));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int point, dir; cin >> point >> dir;
            board[i][j].has_fish = true;
            board[i][j].point = point;
            board[i][j].direction = dir;
        }
    }

    backtrack(0, 0, 0, board);
    
    cout << answer << "\n";
    
    return 0;
}