#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 21

#define UP      0
#define RIGHT   1
#define DOWN    2
#define LEFT    3

using namespace std;

int N;                  // 세로 크기
int M;                  // 가로 크기
int K;                  // 이동 횟수
int dir = RIGHT;        // 방향

int curx = 1;           // 지도에 위치한 주사위의 x좌표 (세로축)
int cury = 1;           // 지도에 위치한 주사위의 y좌표 (가로축)

int board[MAX][MAX];    // 지도
int adj_board[MAX][MAX];// 연속된 값이 몇 개 있는지 확인
int dice[4][3] = {      // 주사위의 상태 (전개도)
        {0, 2, 0},
        {4, 1, 3},
        {0, 5, 0},
        {0, 6, 0}
    };        

void move_dice() {

    if (dir == UP) {
        if (curx == 1) { dir = DOWN; curx += 1; }
        else curx -= 1;
    }

    else if (dir == RIGHT) {
        if (cury == M) { dir = LEFT; cury -= 1; }
        else cury += 1;
    }

    else if (dir == DOWN) {
        if (curx == N) { dir = UP; curx -= 1; }
        else curx += 1;
    }

    else if (dir == LEFT) {
        if (cury == 1) { dir = RIGHT; cury += 1; }
        else cury -= 1;
    }
}

void update_dice() {
    if (dir == UP) {
        int top = dice[0][1];

        for (int i = 0; i < 3; ++i) dice[i][1] = dice[i + 1][1];
        dice[3][1] = top;
    }

    else if (dir == RIGHT) {
        int right = dice[1][2];

        dice[1][2] = dice[1][1];
        dice[1][1] = dice[1][0];
        dice[1][0] = dice[3][1];
        dice[3][1] = right;
    }

    else if (dir == DOWN) {
        int bottom = dice[3][1];

        dice[3][1] = dice[2][1];
        dice[2][1] = dice[1][1];
        dice[1][1] = dice[0][1];
        dice[0][1] = bottom;
    }

    else if (dir == LEFT) {
        int left = dice[1][0];

        dice[1][0] = dice[1][1];
        dice[1][1] = dice[1][2];
        dice[1][2] = dice[3][1];
        dice[3][1] = left;
    }
}

void update_dir(int bottom, int cell) {
    if (bottom > cell) {
        dir += 1;
        dir %= 4;
    }

    else if (bottom < cell) {
        dir -= 1;
        if (dir < 0) dir = 3;
    }
}

void bfs(int x, int y, int val) {
    adj_board[x][y] = 1;

    queue<pii> q;
    q.push({x, y});

    vector<pii> grp;
    grp.push_back({x, y});

    while (!q.empty()) {
        int herex = q.front().first;
        int herey = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int therex = herex + ("2110"[i] - '0') - 1;
            int therey = herey + ("1201"[i] - '0') - 1;

            if (therex <= 0 || therey <= 0 || therex > N || therey > M) continue;
            if (adj_board[therex][therey] != 0 || board[therex][therey] != val) continue;
            
            adj_board[therex][therey] = 1;
            grp.push_back({therex, therey});
            q.push({therex, therey});
        }
    }

    int grp_size = grp.size();
    for (pii pos : grp) adj_board[pos.first][pos.second] = grp_size;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 1. input
    cin >> N >> M >> K;

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> board[i][j];

    // 2. 같은 수가 몇개 연결되어 있는가? -> adj_board[i][j] 에 저장
    memset(adj_board, 0, sizeof(adj_board));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            if (adj_board[i][j] == 0)
                bfs(i, j, board[i][j]);

    // 3. K 번 주사위를 굴려 테스트
    int score = 0;
    while (K--) {
        move_dice();                        // 주사위 이동
        update_dice();                      // 주사위 전개도 업데이트

        int bottom = dice[3][1];            // 주사위의 밑면
        int curPos = board[curx][cury];     // 현재 주사위가 위치한 지도의 숫자
        int adjCnt = adj_board[curx][cury]; // 지도의 숫자가 몇개 연결되어 있는지?

        score += curPos * adjCnt;           // 점수 계산

        update_dir(bottom, curPos);         // 방향 업데이트
    }

    cout << score << "\n";

    return 0;
}