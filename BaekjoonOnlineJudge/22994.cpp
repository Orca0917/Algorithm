#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

char board[1000][1000];
int n, m; 

// O(nm)
bool check(int i, int j) {
    for (int row = 0; row < n; row += i) {
        for (int col = 0; col < m; col += j) {

            // [row, row + i), [col, col + j) 같아야 함
            for (int ii = row; ii < row + i; ++ii)
                for (int jj = col; jj < col + j; ++jj)
                    if (board[ii][jj] != board[row][col])
                        return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 확대된 정보 입력받기
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    int area = 1e9;
    pii answer = {1, 1};

    for (int i = 1; i <= n; ++i) {
        if (n % i) continue;
        for (int j = 1; j <= m; ++j) {
            if (m % j) continue;

            // 행을 i배, 열을 j배
            int original_area = n * m / (i * j);
            if (check(i, j) && area > original_area) {
                area = original_area;
                answer = {i, j};
            }
        }
    }

    cout << n / answer.first << " " << m / answer.second << "\n";
    for (int i = 0; i < n; i += answer.first) {
        for (int j = 0; j < m; j += answer.second) {
            cout << board[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}