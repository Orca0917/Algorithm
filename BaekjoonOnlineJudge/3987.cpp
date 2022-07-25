#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 501

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

int N;                  // 세로
int M;                  // 가로
int curx;               // 보이저의 현재 위치
int cury;               // 보이저의 현재 위치

int use_cnt[MAX][MAX];  // 항성계를 몇 번 이용했는가?
char board[MAX][MAX];   // 우주 지도

int movement[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char c_dir[4] = {'U', 'R', 'D', 'L'};


int send_signal(int dir) {
    memset(use_cnt, 0, sizeof(use_cnt));

    int ret = 0;
    int x = curx, y = cury;

    while (true) {

        // 종료 조건
        if (x <= 0 || y <= 0 || x > N || y > M) break;
        if (board[x][y] == 'C') break;

        // 방향 전환 1
        if (board[x][y] == '/') {
            if (dir == UP || dir == RIGHT) dir ^= (UP ^ RIGHT);
            else dir ^= (LEFT ^ DOWN);

            if (use_cnt[x][y]++ > 2) return -1;
        } 
        // 방향 전환 2
        else if (board[x][y] == '\\') {
            if (dir == UP || dir == LEFT) dir ^= (UP ^ LEFT);
            else dir ^= (DOWN ^ RIGHT);

            if (use_cnt[x][y]++ > 2) return -1;
        }

        ++ret;
        x += movement[dir][0];
        y += movement[dir][1];
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;
    
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> board[i][j];

    cin >> curx >> cury;

    int answer = 0;
    int answer_dir = 0;

    for (int dir = 0; dir < 4; ++dir) {
        int value = send_signal(dir);
        if (value == -1) {
            answer_dir = dir;
            answer = -1;
            break;
        }

        else if (answer < value) {
            answer_dir = dir;
            answer = value;
        }
    }

    if (answer == -1) cout << c_dir[answer_dir] << "\nVoyager\n";
    else cout << c_dir[answer_dir] << "\n" << answer << "\n";
    
    return 0;
}