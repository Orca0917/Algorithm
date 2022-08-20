#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int board[51][51];
        memset(board, 0, sizeof(board));
        int n, m; cin >> n >> m;
        int start = 1;

        for (int i = 0; i < n; ++i) {
            if (i > 1) start = board[i - 2][0] ^ 1;
            else if (i == 1) start = 0;

            for (int j = 0; j < m; j += 2) {
                board[i][j] = start;
                board[i][j + 1] = start ^ 1;
                start ^= 1;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}