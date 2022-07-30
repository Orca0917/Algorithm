#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;


int R;              // 세로
int C;              // 가로
int answer = 0;     // 정답
char board[21][21]; // 표 모양의 보드

void dfs(int x, int y, int cnt, vector<bool> &his) {

    answer = max(answer, cnt);

    for (int i = 0; i < 4; ++i) {
        int nx = x + ("2110"[i] - '0') - 1;
        int ny = y + ("1201"[i] - '0') - 1;

        if (nx < 1 || ny < 1 || nx > R || ny > C) continue;
        if (his[board[nx][ny] - 'A']) continue;

        his[board[nx][ny] - 'A'] = true;
        dfs(nx, ny, cnt + 1, his);
        his[board[nx][ny] - 'A'] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C;

    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j)
            cin >> board[i][j];
    }

    vector<bool> history(30, false);
    history[board[1][1] - 'A'] = true;
    dfs(1, 1, 1, history);

    cout << answer << "\n";
    
    return 0;
}