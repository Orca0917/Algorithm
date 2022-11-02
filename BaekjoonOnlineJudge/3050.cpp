#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int board[401][401];
int psum[401][401];
pii table[401][401];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 배열 0으로 초기화
    memset(board, 0, sizeof(board));
    memset(psum, 0, sizeof(psum));
    memset(table, 0, sizeof(table));
    
    // 입력
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char cell; cin >> cell;
            if (cell == 'X') board[i][j] = 0;
            else {
                board[i][j] = 1;
                table[i][j] = {1, 1};
            }
        }
    }


    for (int i = 1; i < n; ++i) {
        if (board[i][0] == 1) {
            table[i][0].first = table[i - 1][0].first + 1;
        }
    }

    for (int j = 1; j < m; ++j) {
        if (board[0][j] == 1) {
            table[0][j].second = table[0][j - 1].second + 1;
        }
    }

    int answer = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (board[i][j] == 1) {
                pii left = table[i][j - 1];
                pii up = table[i - 1][j];
                
                table[i][j].first = max(1, min(left.first, up.first + 1));
                table[i][j].second = max(1, min(left.second + 1, up.second));

                cout << table[i][j].first << ", " << table[i][j].second << "\n";
                answer = max(answer, table[i][j].first * 2 + table[i][j].second * 2);
            }
        }
    }
    
    
    cout << answer - 1 << "\n";

    return 0;
}