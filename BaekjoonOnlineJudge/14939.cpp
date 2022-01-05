#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

char bulb[11][11];
char temp[11][11];

void bulbSwitch(int x, int y) {
    for (int i = 0; i < 5; ++i) {
        int nx = x + "21101"[i] - '1';
        int ny = y + "12011"[i] - '1';
        if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10) continue;
        temp[nx][ny] ^= ('#' ^ 'O');
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            cin >> bulb[i][j];

    int answer = 10000;
    for (int B = 0; B < (1 << 10); ++B) {

        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                temp[i][j] = bulb[i][j];

        int cnt = 0;
        for (int bit = 0; bit < 10; ++bit) {
            if (B & (1 << bit)) {
                ++cnt;
                bulbSwitch(0, bit);
            }
        }

        for (int row = 1; row < 10; ++row) {
            for (int col = 0; col < 10; ++col) {
                if (temp[row - 1][col] == 'O') {
                    ++cnt;
                    bulbSwitch(row, col);
                }
            }
        }

        bool flag = false;
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                if (temp[i][j] == 'O')
                    flag = true;

        if (flag) continue;
        answer = min(answer, cnt);
    }

    if (answer == 10000) cout << "-1\n";
    else cout << answer << "\n";

    return 0;
}