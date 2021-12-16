/*
 * author: 0917jong
 * date: 2021-12-16
 */

#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    // 주어진 동전의 정보를 입력받기
    int n; cin >> n;

    char board[21][21];
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> board[i][j]; 

    int answer = n * n;
    for (int comb = 0; comb < (1 << n); ++comb) {
        int result = 0;
        for (int col = 0; col < n; ++col) {
            int cntT = 0;
            for (int row = 0; row < n; ++row) {
                char val = board[row][col];
                if (comb & (1 << row)) val ^= ('H' ^ 'T');
                if (val == 'T') ++cntT;
            }
            result += min(cntT, n - cntT);
        }
        answer = min(answer, result);
    }

    cout << answer << "\n";
    return 0;
}