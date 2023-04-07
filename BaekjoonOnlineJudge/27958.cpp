#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 9
using namespace std;

struct Target {
    int current_health = 0; // 현재 체력
    int initial_health = 0; // 초기 체력

    // 이 타겟에 사격한 결과
    int shoot(int damage) {
        current_health = max(0, current_health - damage);
        if (initial_health >= 10) current_health = 0;
        return (current_health == 0 ? initial_health : 0);
    }

    // 새로운 타겟 설정
    void set_target(int health) {
        current_health = health;
        initial_health = health;
    }
};


int board_size; // 게임판의 크기
int num_shot;   // 사격 횟수
int max_score = 0;
int movement[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<int> bullet_attk;


// 배열 복사해주는 함수: copy_board <- board
void copy(vector<vector<Target>> &copy_board, vector<vector<Target>> board) {
    for (int i = 0; i < board_size; ++i)
        for (int j = 0; j < board_size; ++j)
            copy_board[i][j] = board[i][j];
}


// 현재 타겟 주변에 있는 빈 공간 탐색
vector<pii> make_new_target(vector<vector<Target>> &copy_board, int row, int col) {
    vector<pii> ret;

    for (int i = 0; i < 4; ++i) {
        int xx = row + movement[i][0];
        int yy = col + movement[i][1];

        if (xx < 0 || xx >= board_size || yy < 0 || yy >= board_size) continue;
        if (copy_board[xx][yy].current_health > 0) continue;

        ret.push_back({xx, yy});
    }

    return ret;
}


// 가능핞 모든 경우의 수로 게임 진행
void do_game(vector<vector<Target>> board, int bullet_index, int cur_score) {


    // 총알을 모두 사용함
    if (bullet_index == num_shot) {
        max_score = max(max_score, cur_score);
        return;
    }

    // 총을 각 줄에서 한 번씩 쏴보기
    for (int row = 0; row < board_size; ++row) {
        // 1. 현재 row에서 가장 가까이 있는 타겟 검색하기
        int col = 0;
        while (board[row][col].current_health == 0 && col < board_size) ++col;

        // 2. 이번 row에서는 사격 대상이 존재하지 않음
        if (col == board_size) continue;

        // 3. board를 copy_board로 복사
        vector<vector<Target>> copy_board(MAX, vector<Target>(MAX));
        copy(copy_board, board);

        // 4. board[row][col]를 사격하고 점수 획득
        int point = copy_board[row][col].shoot(bullet_attk[bullet_index]);

        // 5. 보너스 타겟이 아닌데 죽은 경우: 주변에 적 생성
        vector<pii> new_target_pos;
        if (copy_board[row][col].current_health == 0 && copy_board[row][col].initial_health < 10)
            new_target_pos = make_new_target(copy_board, row, col);

        int new_health = copy_board[row][col].initial_health / 4;
        for (pii pos : new_target_pos) copy_board[pos.first][pos.second].set_target(new_health); // 적생성

        do_game(copy_board, bullet_index + 1, cur_score + point);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 보드판의 크기, 사격횟수
    cin >> board_size >> num_shot;

    vector<vector<Target>> board(MAX, vector<Target>(MAX));
    // 보드판의 정보 입력받기 
    for (int i = 0; i < board_size; ++i)
        for (int j = 0; j < board_size; ++j) {
            Target &target = board[i][j];
            cin >> target.initial_health;
            target.current_health = target.initial_health;
        }

    // 총알의 공격력 입력받기
    bullet_attk.resize(num_shot);
    for (int &attk : bullet_attk) cin >> attk;

    do_game(board, 0, 0);
    
    cout << max_score << "\n";

    return 0;
}