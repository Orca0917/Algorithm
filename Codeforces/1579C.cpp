#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

char board[11][20];
bool hasColored[11][20];
int n, m, k, draw;

bool checkIsTick(int x, int y) {
    //check Left
    int tx = x, ty = y, tc1 = 0;
    while (tx >= 0 && ty >= 0) {
        if (board[tx][ty] != '*') break;
        --tx;
        --ty;
        ++tc1;
    }
    if (tc1 <= k) return false;

    // check Right
    tx = x, ty = y;
    int tc2 = 0;
    while (tx >= 0 && ty < m) {
        if (board[tx][ty] != '*') break;
        --tx;
        ++ty;
        ++tc2;
    }
    if (tc2 <= k) return false;
    draw = min(tc1, tc2);
    return true;
}

void colorTick(int x, int y) {
    int tx = x, ty = y, tc = 0, d = draw;
    while (tx >= 0 && ty >= 0 && d--) {
        if (board[tx][ty] != '*') break;
        hasColored[tx][ty] = true;
        --tx;
        --ty;
        ++tc;
    }
    
    tx = x, ty = y, d = draw;
    while (tx >= 0 && ty < m && d--) {
        if (board[tx][ty] != '*') break;
        hasColored[tx][ty] = true;
        --tx;
        ++ty;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        // boardsize, number of tick
        cin >> n >> m >> k;
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> board[i][j];

        memset(hasColored, false, sizeof(hasColored));
        int tickCount = 0; 
        
        // find ticks
        for (int row = n - 1; row >= 0; --row) {
            for (int col = m - 1; col >= 0; --col) {
                if (board[row][col] == '*') {
                    bool res = checkIsTick(row, col);
                    if (res) {
                        colorTick(row, col);
                    }
                }
            }
        }
        

        bool answer = true;
        for (int i = 0; i < n && answer; ++i)
            for (int j = 0; j < m && answer; ++j)
                if (board[i][j] == '*' && hasColored[i][j] == false)
                    answer = false;
        

        if (answer) cout << "YES\n";
        else cout << "NO\n";
        
    }
    return 0;
}