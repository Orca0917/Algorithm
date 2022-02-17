#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int board[202][202];
ll psum[202][202];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            psum[i][j] = board[i][j];
            cin >> board[i][j];
        }

    memset(psum, 0LL, sizeof(psum));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            psum[i][j] = psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1] + board[i][j];
        }
    }

    ll answer = -4LL * 1e10;
    for (int startX = 1; startX <= n; ++startX) {
        for (int startY = 1; startY <= m; ++startY) {
            for (int endX = startX; endX <= n; ++endX) {
                for (int endY = startY; endY <= m; ++endY) {
                    // (startX, startY) ~ (endX, endY) 에 해당하는 면적
                    answer = max(answer, psum[endX][endY] - psum[startX - 1][endY] - psum[endX][startY - 1] + psum[startX - 1][startY - 1]);
                }
            }
        }
    }

    cout << answer << "\n";
    return 0;
}