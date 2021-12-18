#include <bits/stdc++.h>
using namespace std;

//// init values /////
int n, m;
char board[11][11];
int memo[11][(1 << 11)];
/////////////////////////

int dp(int row, int prevSeats) {
    // 좌석의 가장 뒷줄에 도착하여 더이상 확인할 것이 없음.
    if (row == n) return 0;

    int &ret = memo[row][prevSeats];
    if (ret != -1) return ret;

    ret = 0;
    for (int seats = 0; seats < (1 << m); ++seats) {
        bool canCheat = false; // 현재 좌석 배정으로 컨닝이 가능한지 판단한다.

        // 현재 배치가 불가능한 경우: 컨닝이 가능한 경우 + 좌석이 파손된 경우
        // 1. 나의 좌, 우에 앉는 경우
        // 2. 대각선자리에 앉는 경우
        // 3. 자리가 파손된 경우

        // 먼저 옆자리에 사람이 앉는 경우를 제외한다.
        for (int j = 0; j < m && !canCheat; ++j) {
            bool opt1 = seats & (1 << j); // 현재 자리에 사람이 있는지
            bool opt2 = (j > 0) && (seats & (1 << (j - 1))); // 현재 왼쪽 자리에 사람이 잇는지
            if (opt1 && opt2) {
                // cout << "옆자리에 사람이 있어서 앉지 못함\n";
                canCheat = true;
            }
        }

        // 대각선 자리에 사람이 앉는 경우를 제외한다.
        for (int j = 0; j < m && !canCheat; ++j) {
            bool opt1 = seats & (1 << j); // 현재 자리에 사람이 있는지
            bool opt2 = (j > 0) && (prevSeats & (1 << (j - 1))); // 대각선 왼쪽에 사람이 있는지
            bool opt3 = (j < m - 1) && (prevSeats & (1 << (j + 1))); // 대각선 오른쪽에 사람이 있는지
            if (opt1 && (opt2 || opt3)) {
                // cout << "대각선에 사람이 있어서 앉지 못함\n";
                canCheat = true;
            }
        }

        // 예외: 현재 자리가 파손된 경우
        for (int j = 0; j < m && !canCheat; ++j) {
            bool opt1 = seats & (1 << j);
            bool opt2 = (board[row][j] == 'x');
            if (opt1 && opt2) {
                // cout << "자리가 파손되어서 앉지 못함\n";
                canCheat = true;
            }
        }

        if (canCheat) continue;

        int studentCount = 0; // 현재 row줄에 몇 명이 앉을 수 있는지 확인한다.
        for (int i = 0; i < m; ++i) if (seats & (1 << i)) studentCount++;

        ret = max(ret, dp(row + 1, seats) + studentCount);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        memset(memo, -1, sizeof(memo));

        cin >> n >> m;
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> board[i][j];

        cout << dp(0, 0) << "\n";
    }

    return 0;
}