#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3

using namespace std;

int movement[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

int board[501][501];
int direction = LEFT;
int answer = 0;
int n;


double LEFT_MOVE[5][5] = {
    {0, 0, 0.02, 0, 0},
    {0, 0.1, 0.07, 0.01, 0},
    {0.05, 0, 0, 0, 0},
    {0, 0.1, 0.07, 0.01, 0},
    {0, 0, 0.02, 0, 0},
};

double RIGHT_MOVE[5][5] = {
    {0, 0, 0.02, 0, 0},
    {0, 0.01, 0.07, 0.1, 0},
    {0, 0, 0, 0, 0.05},
    {0, 0.01, 0.07, 0.1, 0},
    {0, 0, 0.02, 0, 0}
};

double DOWN_MOVE[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0.01, 0, 0.01, 0},
    {0.02, 0.07, 0, 0.07, 0.02},
    {0, 0.1, 0, 0.1, 0},
    {0, 0, 0.05, 0, 0}
};

double UP_MOVE[5][5] = {
    {0, 0, 0.05, 0, 0},
    {0, 0.1, 0, 0.1, 0},
    {0.02, 0.07, 0, 0.07, 0.02},
    {0, 0.01, 0, 0.01, 0},
    {0, 0, 0, 0, 0}
};


void spread_sand(double matrix[5][5], int current, int x, int y) {

    int total = 0, xx, yy;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            xx = x + (i - 2);
            yy = y + (j - 2);
            int amount = current * matrix[i][j];
            
            total += amount;

            if (xx < 0 || xx >= n || yy < 0 || yy >= n) answer += amount;
            else board[xx][yy] += amount;
        }
    }

    int left = current - total;
    xx = x + movement[direction][0];
    yy = y + movement[direction][1];

    if (xx < 0 || xx >= n || yy < 0 || yy >= n) answer += left;
    else board[xx][yy] += left;
}


void tornado_move(int x, int y, int direction) {

    // [x, y] 에 있는 모래가 퍼짐
    int current = board[x][y];
    board[x][y] = 0;

    // spread 5 %
    if (direction == UP) spread_sand(UP_MOVE, current, x, y);
    else if (direction == DOWN) spread_sand(DOWN_MOVE, current, x, y);
    else if (direction == LEFT) spread_sand(LEFT_MOVE, current, x, y);
    else if (direction == RIGHT) spread_sand(RIGHT_MOVE, current, x, y);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> board[i][j];

    pii pos = {n / 2, n / 2};

    int max_move = 1;
    int move_cnt = 0;
    int dir_cnt = 0;
    
    while (pos.first != 0 || pos.second != 0) {

        // direction 방향으로 1칸 이동
        pos.first += movement[direction][0];
        pos.second += movement[direction][1];
        
        tornado_move(pos.first, pos.second, direction);

        // direction 전환
        if (++dir_cnt == max_move) {
            dir_cnt = 0;
            direction = (++direction) % 4;
        }

        // move_count 증가
        if (++move_cnt == max_move * 2) {
            move_cnt = 0;
            max_move += 1;
        }

    }

    cout << answer << "\n";
    
    return 0;
}