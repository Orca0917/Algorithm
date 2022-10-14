#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    char board[51][51];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            char &now = board[i][j];
            if (now == 'o') {
                now = '.';
                int x = i, y = j;
                while (x < n && board[x + 1][y] == '.') ++x;
                board[x][y] = 'o';
            }
        }
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << board[i][j];
        cout << "\n";
    }
    
    return 0;
}