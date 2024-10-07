#include <bits/stdc++.h>
using namespace std;

// 7세그먼트 디스플레이에서 각 숫자별 세그먼트 위치 정의
vector<vector<int>> segment_positions = {
    {1, 2, 3, 5, 6, 7}, // 0
    {3, 6},             // 1
    {1, 3, 4, 5, 7},    // 2
    {1, 3, 4, 6, 7},    // 3
    {2, 3, 4, 6},       // 4
    {1, 2, 4, 6, 7},    // 5
    {1, 2, 4, 5, 6, 7}, // 6
    {1, 3, 6},          // 7
    {1, 2, 3, 4, 5, 6, 7}, // 8
    {1, 2, 3, 4, 6, 7}, // 9
};

// 주어진 숫자를 7세그먼트 디스플레이 형식으로 그리는 함수
void draw_seven_segment(int size, const string& digits) {
    // 디스플레이 패널을 공백으로 초기화
    char display[30][150];
    memset(display, ' ', sizeof(display));

    // 각 숫자에 대해 세그먼트를 그리는 작업
    for (int i = 0; i < digits.length(); ++i) {
        int padding = (size + 2) * i + i + 1; // 각 숫자 사이의 간격 계산
        int current_digit = digits[i] - '0';  // 현재 숫자

        // 현재 숫자의 각 세그먼트 위치에 맞게 '-' 또는 '|' 추가
        for (int position : segment_positions[current_digit]) {
            if (position == 1 || position == 4 || position == 7) {
                // 가로줄 세그먼트 그리기 (1, 4, 7 위치)
                int row = (position - 1) / 3 * (size + 1);
                for (int j = 0; j < size; ++j) {
                    display[row][padding + j] = '-';
                }
            } else if (position == 2 || position == 5) {
                // 왼쪽 세로줄 그리기 (2, 5 위치)
                int column = padding - 1;
                int row = (position == 2 ? 1 : size + 2);
                for (int j = 0; j < size; ++j)
                    display[row + j][column] = '|';
            } else if (position == 3 || position == 6) {
                // 오른쪽 세로줄 그리기 (3, 6 위치)
                int column = padding + size;
                int row = (position == 3 ? 1 : size + 2);
                for (int j = 0; j < size; ++j)
                    display[row + j][column] = '|';
            }
        }
    }

    // 디스플레이 크기 계산
    int total_rows = 2 * size + 3;
    int total_columns = (size + 2) * digits.length() + digits.length() - 1;

    // 결과 출력
    for (int i = 0; i < total_rows; ++i) {
        for (int j = 0; j < total_columns; ++j) {
            cout << display[i][j];
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int size; 
    string input_digits;

    // 입력 받기
    cin >> size >> input_digits;

    // 숫자를 7세그먼트로 그리기
    draw_seven_segment(size, input_digits);
    
    return 0;
}
