#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 드래곤 커브의 개수 (1 ~ 20)
int x, y; // 드래곤 커브의 시작점
int d; // 시작 방향 (0우, 1상, 2좌, 3하)
int g; // 세대

bool board[1001][1001];

void dragon_curve(int x, int y, int dir, int gen) {
    if (gen == 0) return;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(board, false, sizeof(board));
    cin >> N;
    while (N--) {
        cin >> y >> x >> d >> g;

        vector<int> dir_list;

        board[x][y] = true;
        x = x + "1012"[d] - '0' - 1;
        y = y + "2101"[d] - '0' - 1;
        board[x][y] = true;
        dir_list.push_back(d);

        for (int j = 0; j < g; ++j) {
            for (int k = dir_list.size() - 1; k >= 0; --k) {
                int d = (dir_list[k] + 1) % 4;
                x = x + "1012"[d] - '0' - 1;
                y = y + "2101"[d] - '0' - 1;
                board[x][y] = true;
                dir_list.push_back(d);
            }
        }

        dir_list.clear();
    }

    int result = 0;
    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j) {
            if (board[i][j] == true && board[i + 1][j] == true && board[i][j + 1] == true && board[i + 1][j + 1] == true)
                result += 1;
        }

    cout << result << "\n";
    return 0;
}