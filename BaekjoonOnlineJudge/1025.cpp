#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N, M, answer = -1;
int A[10][10];

void checkNum(int row, int col, int diff1, int diff2) {
    int x = row, y = col;

    int number = 0;
    while (true) {
        if (x < 0 || x >= N || y < 0 || y >= M) break;
        number = number * 10 + A[x][y];
        x += diff1;
        y += diff2;

        int square = (int)sqrt(number);
        if (square * square == number) answer = max(answer, number);
    }
}

void makeDiff(int row, int col) {

    int d1 = -9;
    int d2 = -9;

    for (int i = d1; i <= 9; ++i)
        for (int j = d2; j <= 9; ++j) {
            if (i == 0 && j == 0) continue;
            checkNum(row, col, i, j);
        }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            char c; cin >> c;
            A[i][j] = c - '0';
        }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            makeDiff(i, j);

    cout << answer << "\n";
    
    return 0;
}