#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int board[51][51];
ll psum[51][51];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            board[i][j] = c - '0';
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // psum[i][j] = psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + board[i][j];
            psum[i][j] = board[i][j];
            if (i - 1 >= 0) psum[i][j] += psum[i - 1][j];
            if (j - 1 >= 0) psum[i][j] += psum[i][j - 1];
            if (i - 1 >= 0 && j - 1 >= 0) psum[i][j] -= psum[i - 1][j - 1];
        }
    }

    ll answer = 0;

    // 세로로로 3 분할
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            ll ret = psum[n - 1][i] * (psum[n - 1][j] - psum[n - 1][i]) * (psum[n - 1][m - 1] - psum[n - 1][j]); 
            answer = max(answer, ret);
        }
    }
    // 가로로 3 분할
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll ret = psum[i][m - 1] * (psum[j][m - 1] - psum[i][m - 1]) * (psum[n - 1][m - 1] - psum[j][m - 1]); 
            answer = max(answer, ret);
        }
    }

    // ㅗ, ㅜ, ㅏ, ㅓ 분할
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // ㅏ
            ll ret = psum[n - 1][j] * (psum[i][m - 1] - psum[i][j]) * (psum[n - 1][m - 1] - psum[i][m - 1] - psum[n - 1][j] + psum[i][j]);
            answer = max(ret, answer);

            // ㅓ
            ret = psum[i][j] * (psum[n - 1][j] - psum[i][j]) * (psum[n - 1][m - 1] - psum[n - 1][j]);
            answer = max(ret, answer);

            // ㅗ
            ret = psum[i][j] * (psum[i][m - 1] - psum[i][j]) * (psum[n - 1][m - 1] - psum[i][m - 1]);
            answer = max(ret, answer);

            // ㅜ
            ret = psum[i][m - 1] * (psum[n - 1][j] - psum[i][j]) * (psum[n - 1][m - 1] - psum[i][m - 1] - psum[n - 1][j] + psum[i][j]);
            answer = max(ret, answer);
        }
    }

    cout << answer << "\n";
    return 0;
}