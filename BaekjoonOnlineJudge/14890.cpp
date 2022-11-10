#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N, L;
int psum[101][101][2];
int board[101][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> L;

    memset(psum, 0, sizeof(psum));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> board[i][j];
        }
    }

    // 누적합 계산
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            psum[i][j][0] = psum[i][j - 1][0] + board[i][j];
            psum[i][j][1] = psum[i - 1][j][1] + board[i][j];
        }
    }


    int answer = 0;

    // 행 확인
    for (int row = 1; row <= N; ++row) {
        bool is_possible = true;
        set<int> placement;

        for (int col = 2; col <= N && is_possible; ++col) {
            int diff = board[row][col] - board[row][col - 1];

            if (abs(diff) == 1) {
                if (diff == 1) { // 오르막길

                    // 경사로를 설치하여 이동할 수 있음
                    if (col - L >= 1 && psum[row][col - 1][0] - psum[row][col - L - 1][0] == L * board[row][col - 1]) {

                        // 이전 L개의 칸에 경사로가 이미 설치된 기록이 없음
                        if (placement.lower_bound(col - L) == placement.end()) {
                            placement.insert(col - 1);
                            continue;
                        }
                    }

                    // 경사로의 설치가 불가능
                    is_possible = false;
                }

                else if (diff == -1) {  // 내리막길

                    // 경사로를 설치하여 이동할 수 있음
                    if (col + L - 1 <= N && psum[row][col + L - 1][0] - psum[row][col - 1][0] == L * board[row][col]) {

                        // 이전 L개의 칸에 경사로가 이미 설치된 기록이 없음
                        if (placement.lower_bound(col) == placement.end()) {
                            placement.insert(col + L - 1);
                            continue;
                        }
                    }

                    // 경사로의 설치가 불가능
                    is_possible = false;
                }
            }

            else if (abs(diff) > 1) is_possible = false;
        }
        answer += (int)is_possible;
    }


    // 행 확인
    for (int col = 1; col <= N; ++col) {
        bool is_possible = true;
        set<int> placement;

        for (int row = 2; row <= N && is_possible; ++row) {
            int diff = board[row][col] - board[row - 1][col];

            if (abs(diff) == 1) {
                if (diff == 1) { // 오르막길

                    // 경사로를 설치하여 이동할 수 있음
                    if (row - L >= 1 && psum[row - 1][col][1] - psum[row - L - 1][col][1] == L * board[row - 1][col]) {

                        // 이전 L개의 칸에 경사로가 이미 설치된 기록이 없음
                        if (placement.lower_bound(row - L) == placement.end()) {
                            placement.insert(row - 1);
                            continue;
                        }
                    }

                    // 경사로의 설치가 불가능
                    is_possible = false;
                }


                else {  // 내리막길

                    // 경사로를 설치하여 이동할 수 있음
                    if (row + L - 1 <= N && psum[row + L - 1][col][1] - psum[row - 1][col][1] == L * board[row][col]) {

                        // 이전 L개의 칸에 경사로가 이미 설치된 기록이 없음
                        if (placement.lower_bound(row) == placement.end()) {
                            placement.insert(row + L - 1);
                            continue;
                        }
                    }

                    // 경사로의 설치가 불가능
                    is_possible = false;
                }
            }
            else if (abs(diff) > 1)
                is_possible = false;
        }
        answer += (int)is_possible;
    }

    cout << answer << "\n";
    
    return 0;
}