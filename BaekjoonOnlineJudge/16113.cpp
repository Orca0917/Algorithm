#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int signal_len; // 시그널의 길이
string sig;  // 시그널 문자열

string board[5];

int get_dot_cnt(int col) {
    int cnt = 0;

    for (int i = 0; i < 5; ++i)
        if (board[i][col] == '.')
            ++cnt;

    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> signal_len >> sig;

    int one_line = signal_len / 5;

    // 한 줄을 5줄로 나누어서 board에 담기
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < one_line; ++j)
            board[i].push_back(sig[i * one_line + j]);

    // 각 행에 맨 뒤에 . 추가
    for (int i = 0; i < 5; ++i) board[i].push_back('.');
    
    string answer = "";
    for (int col = 0, jump = 3; col < one_line; col += jump) {
        int number1 = get_dot_cnt(col);
        if (number1 == 5) {
            jump = 1;
            continue;
        }

        int number2 = get_dot_cnt(col + 1);
        int number3 = get_dot_cnt(col + 2);

        jump = 3;
        if (number1 == 0 && number2 == 3 && number3 == 0) answer += "0";
        else if (number1 == 0 && number2 == 5) {answer += "1"; jump = 1;}
        else if (number1 == 2 && number2 == 2 && number3 == 0) answer += "3";
        else if (number1 == 2 && number2 == 4 && number3 == 0) answer += "4";
        else if (number1 == 0 && number2 == 2 && number3 == 1) answer += "6";
        else if (number1 == 4 && number2 == 4 && number3 == 0) answer += "7";
        else if (number1 == 0 && number2 == 2 && number3 == 0) answer += "8";
        else if (number1 == 1 && number2 == 2 && number3 == 0) answer += "9";
        else {
            if (board[1][col] == '#') answer += "5";
            else answer += "2";
        }
    }

    cout << answer << "\n";

    return 0;
}