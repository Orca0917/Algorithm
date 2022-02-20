#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll board[2001][2001];
ll psum[2001][2001];
ll answer[2001][2001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(psum, 0LL, sizeof(psum));
    memset(answer, 0LL, sizeof(answer));

    int m, n; cin >> m >> n;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> board[i][j];
            psum[i][j] = psum[i][j - 1] + board[i][j];
        }
    
    int len = n / 2;

    for (int i = len + 1; i <= m - len; ++i) {
        for (int j = len + 1; j <= m - len; ++j) {
            answer[i][j] = board[i - len][j - len];
            if (i - len - 1 >= 0 && j - len >= 0) answer[i][j] -= board[i - len - 1][j - len];
            if (i - len >= 0 && j - len - 1 >= 0) answer[i][j] -= board[i - len][j - len - 1];
            if (i - len - 1 >= 0 && j - len - 1 >= 0) answer[i][j] += board[i - len - 1][j - len - 1];

            if (i - n >= 0) answer[i][j] += answer[i - n][j];
            if (j - n >= 0) answer[i][j] += answer[i][j - n];
            if (i - n >= 0 && j - n >= 0) answer[i][j] -= answer[i - n][j - n];
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j)
            cout << -answer[i][j] << " ";
        cout << "\n";
    }
    return 0;
}