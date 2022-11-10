#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

#define ON '#'
#define OFF '.'
using namespace std;

char board[5][50];
int n;

string digits[10][5] = {
   {
    "###",
    "#.#",
    "#.#",
    "#.#",
    "###"
   },
   {
    "..#",
    "..#",
    "..#",
    "..#",
    "..#"
   },
   {
    "###",
    "..#",
    "###",
    "#..",
    "###"
   },
   {
    "###",
    "..#",
    "###",
    "..#",
    "###"
   },
   {
    "#.#",
    "#.#",
    "###",
    "..#",
    "..#"
   },
   {
    "###",
    "#..",
    "###",
    "..#",
    "###"
   },
   {
    "###",
    "#..",
    "###",
    "#.#",
    "###"
   },
   {
    "###",
    "..#",
    "..#",
    "..#",
    "..#"
   },
   {
    "###",
    "#.#",
    "###",
    "#.#",
    "###"
   },
   {
    "###",
    "#.#",
    "###",
    "..#",
    "###"
   },
};

/**
 * @brief 현재 5x3 크기의 안내판 상태가 들어왔을 때, 가능한 숫자 목록을 반환
 * 원래 켜진 곳이 꺼져있는 것은 가능
 * 원래 꺼진 곳이 켜져있는 것은 불가능
 * @param index 
 * @return vector<int> 
 */
vector<int> discriminate(int index) {
    vector<int> ret;
    for (int num = 0; num < 10; ++num) {
        bool possible = true;
        for (int i = 0; i < 5 && possible; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][index + j] == ON && digits[num][i][j] == OFF) {
                    possible = false;
                    break;
                }
            }
        }
        if (possible) ret.push_back(num);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cout << fixed;
    cout.precision(9);

    cin >> n;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4 * n - 1; ++j) {
            cin >> board[i][j];
        }
    }

    double answer = 0;
    for (int index = 0; index < 4 * n - 1; index += 4) {
        vector<int> candidate = discriminate(index);

        // 만들 수 있는 후보가 없음 -> 잘못된 sign
        if (candidate.empty()) {
            cout << "-1\n";
            return 0;
        }

        int sum = accumulate(candidate.begin(), candidate.end(), 0);
        answer *= 10;
        answer += sum / (double)candidate.size();
    }

    cout << answer << "\n";
    
    return 0;
}