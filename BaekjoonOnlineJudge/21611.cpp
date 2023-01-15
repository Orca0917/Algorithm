#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Ball {
    int num;
    int x, y;
};

int board[50][50];
int n, m;
int movement[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int answer = 0;
vector<Ball> balls;
set<pii> eraser;
deque<int> transition;


bool isin(int x, int y) {
    return (0 < x && x <= n && 0 < y && y <= n);
}


void make_ball_list() {
    balls.clear();

    int x = (n + 1) / 2;
    int y = (n + 1) / 2;
    int move = 0;

    while (true) {
        move += 1;

        for (int i = 0; i < move; ++i) {
            if (!isin(x, y - 1) || board[x][y - 1] == 0) return;
            balls.push_back({board[x][--y], x, y});
        }

        for (int i = 0; i < move; ++i) {
            if (!isin(x + 1, y) || board[x + 1][y] == 0) return;
            balls.push_back({board[++x][y], x, y});
        }

        move += 1;

        for (int i = 0; i < move; ++i) {
            if (!isin(x, y + 1) || board[x][y + 1] == 0) return;
            balls.push_back({board[x][++y], x, y});
        }

        for (int i = 0; i < move; ++i) {
            if (!isin(x - 1, y) || board[x - 1][y] == 0) return;
            balls.push_back({board[--x][y], x, y});
        }
    }

    balls.pop_back();
}


bool ball_explosion() {
    int cur_num = 0;
    int cur_cnt = 0;
    bool has_explosion = false;

    vector<Ball> new_balls;

    for (Ball &ball : balls) {
        if (eraser.find({ball.x, ball.y}) != eraser.end()) {
            continue;
        }

        if (ball.num == cur_num) {
            cur_cnt += 1;
        } else {
            if (cur_cnt >= 4) {
                has_explosion = true;
                while (cur_cnt--) {
                    answer += new_balls.back().num;
                    new_balls.pop_back();
                }
            }
            cur_num = ball.num;
            cur_cnt = 1;
        }
        new_balls.push_back(ball);
    }

    if (cur_cnt >= 4) {
        has_explosion = true;
        while (cur_cnt--) {
            answer += new_balls.back().num;
            new_balls.pop_back();
        }
    }

    balls.clear();
    balls = vector<Ball>(new_balls.begin(), new_balls.end());

    return has_explosion;
}


void ball_transition() {
    int cur_num = 0;
    int cur_cnt = 0;

    transition.clear();
    for (Ball &ball : balls) {
        if (ball.num == cur_num) {
            cur_cnt += 1;
        } else {
            if (cur_num != 0) {
                transition.push_back(cur_cnt);
                transition.push_back(cur_num);
            }
            cur_num = ball.num;
            cur_cnt = 1;
        }
    }

    transition.push_back(cur_cnt);
    transition.push_back(cur_num);
}


void ball_assign_table() {
    int x = (n + 1) / 2;
    int y = (n + 1) / 2;
    int move = 0;

    memset(board, 0, sizeof(board));
    while (true) {
        move += 1;

        for (int i = 0; i < move; ++i) {
            if (!isin(x, y - 1) || transition.empty()) return;
            board[x][--y] = transition.front();
            transition.pop_front();
        }

        for (int i = 0; i < move; ++i) {
            if (!isin(x + 1, y) || transition.empty()) return;
            board[++x][y] = transition.front();
            transition.pop_front();
        }

        move += 1;

        for (int i = 0; i < move; ++i) {
            if (!isin(x, y + 1) || transition.empty()) return;
            board[x][++y] = transition.front();
            transition.pop_front();
        }

        for (int i = 0; i < move; ++i) {
            if (!isin(x - 1, y) || transition.empty()) return;
            board[--x][y] = transition.front();
            transition.pop_front();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(board, 0, sizeof(board));

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> board[i][j];
    
    while (m--) {
        int dir, dist; cin >> dir >> dist;
        eraser.clear();

        make_ball_list();

        int shark_x = (n + 1) / 2;
        int shark_y = (n + 1) / 2;
        for (int i = 1; i <= dist; ++i)
            eraser.insert({shark_x + movement[dir][0] * i, shark_y + movement[dir][1] * i});

        while (ball_explosion()) ;

        ball_transition();

        ball_assign_table();

    }

    cout << answer << "\n";

    return 0;
}