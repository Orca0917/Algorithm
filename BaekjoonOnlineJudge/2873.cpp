/*
 * author: 0917jong
 * date: 2021-12-12
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int board[1001][1001];

void print(char c, int len) {
    for (int i = 0; i < len; ++i) cout << c;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int r, c; cin >> r >> c;
    

    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            cin >> board[i][j];

    if (r % 2 || c % 2) {
        if (r % 2) {
            for (int i = 0; i < r - 1; i += 2) {
                print('R', c - 1);
                cout << "D";
                print('L', c - 1);
                cout << "D";
            }
            print('R', c - 1);
        } else {
            for (int i = 0; i < c - 1; i += 2) {
                print('D', r - 1);
                cout << "R";
                print('U', r - 1);
                cout << "R";
            }
            print('D', r - 1);
        }
    } else {
        const int inf = 1234567890;
        int minElem = inf;
        pii minCoord;

        // find min coords
        for (int i = 0; i < r; ++i) {
            int st = (i % 2 ? 0 : 1);
            for (int j = st; j < c; j += 2) {
                if (minElem > board[i][j]) {
                    minElem = board[i][j];
                    minCoord = {i, j};
                }
            }
        }

        int lim = (minCoord.first % 2 == 0) ? minCoord.first : minCoord.first - 1;
        // cout << "min coord = " << minCoord.first << ", " << minCoord.second << "\n";
        // cout << "lim = " << lim << "\n";
        // print above section
        // cout << "\n[above section]\n";
        for (int i = 0; i < lim; i += 2) {
            print('R', c - 1);
            cout << "D";
            print('L', c - 1);
            cout << "D";
        }

        // print Up, down section
        // cout << "\n[middle section]\n";
        int j;
        for (j = 0; j < minCoord.second; ++j) {
            if (j % 2) {
                cout << "UR";
            } else {
                cout << "DR";
            }
        }

        if (j < c - 1)
            cout << "R";

        for (j = minCoord.second + 1; j < c - 1; ++j) {
            if (j % 2) {
                cout << "DR";
            } else {
                cout << "UR";
            }
        }

        if (minCoord.first < r - 2) {
            cout << "D";
            if (minCoord.second != c - 1) cout << "D";
        }

        // print below section
        // cout << "\n[below section]\n";
        for (int i = lim + 2; i < r; i += 2){
            print('L', c - 1);
            cout << "D";
            print('R', c - 1);
            if (i != r - 2) cout << "D";
        }
    }
    cout << "\n";
    return 0;
}

