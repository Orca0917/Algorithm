#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define vvi vector<vector<int>>

#define TRASH 1
#define JEWEL 2

#define HORIZONTAL 0
#define VERTICAL 1

using namespace std;

int n; 
vvi board(21, vector<int>(21, 0));


// solve : 현재 board 상태에서 (sx, sy) ~ (ex, ey) 에 존재하는 부분을 탐색
// - sx : 석판의 시작 x
// - sy : 석판의 시작 y
// - ex : 석판의 끝 x
// - ey : 석판의 끝 y
// - now_cur_dir : 현재 석판을 어떤 방향으로 자를 것인지.
int solve(int sx, int sy, int ex, int ey, int now_cut_dir) {

    int left_jewel = 0;     // 현재 조각에 남은 보석의 수
    vector<pii> trashes;      // 현재 석판에 존재하는 불순물 위치

    for (int i = sx; i <= ex; ++i)
        for (int j = sy; j <= ey; ++j)
            if (board[i][j] == TRASH) trashes.push_back({i, j});
            else if (board[i][j] == JEWEL) ++left_jewel;


    // 현재 조각에 남은 불순물이 없어야 하며, 보석은 단 1개 존재해야 한다.
    if (trashes.empty()) {
        if (left_jewel == 1) return 1;
        else return 0;
    }

    int ret = 0;
    for (pii trash : trashes) {
        int x = trash.first;
        int y = trash.second;

        // 수직으로 자르는 경우
        if (now_cut_dir == VERTICAL) {
            // 현재 자르려고 하는 곳에 보석이 존재하는지 확인
            for (int i = sx; i <= ex; ++i) if (board[i][y] == JEWEL) goto OUT;

            // 잘라진 두 부분 석판의 경우의 수를 곱하여 ret에 더해주기
            ret += solve(sx, sy, ex, y - 1, HORIZONTAL) * solve(sx, y + 1, ex, ey, HORIZONTAL);
        }


        // 수평으로 자르는 경우
        else {
            // 현재 자르려고 하는 곳에 보석이 존재하는지 확인
            for (int j = sy; j <= ey; ++j) if (board[x][j] == JEWEL) goto OUT;

            // 잘라진 두 부분 석판의 경우의 수를 곱하여 ret에 더해주기
            ret += solve(sx, sy, x - 1, ey, VERTICAL) * solve(x + 1, sy, ex, ey, VERTICAL);
        }

        OUT:;
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    vector<pii> trash_pos;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> board[i][j];


    int result = solve(0, 0, n - 1, n - 1, HORIZONTAL) + solve(0, 0, n - 1, n - 1, VERTICAL);
    cout << (result == 0 ? -1 : result) << "\n";

    return 0;
}