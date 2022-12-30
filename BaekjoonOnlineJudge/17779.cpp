#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n; 
int board[21][21];
bool vis[21][21];
int total_sum = 0;
int answer = 1e9;

void calculate(int x, int y, int d1, int d2) {
    int ret[6] = {0, 0, 0, 0, 0, 0};

    memset(vis, false, sizeof(vis));
    // 5번 선거구
    for (int i = 0; i <= d1; ++i) vis[x + i][y - i] = true;
    for (int i = 0; i <= d2; ++i) vis[x + i][y + i] = true;
    for (int i = 0; i <= d2; ++i) vis[x + d1 + i][y - d1 + i] = true;
    for (int i = 0; i <= d1; ++i) vis[x + d2 + i][y + d2 - i] = true;

    // 1번 선거구
    for (int i = 1; i < x + d1; ++i) {
        for (int j = 1; j <= y; ++j) {
            if (vis[i][j]) break;
            ret[1] += board[i][j];
        }
    }

    // 2번 선거구
    for (int i = 1; i <= x + d2; ++i) {
        for (int j = n; j > y; --j) {
            if (vis[i][j]) break;
            ret[2] += board[i][j];
        }
    }

    // 3번 선거구
    for (int i = x + d1; i <= n; ++i) { 
        for (int j = 1; j < y - d1 + d2; ++j) {
            if (vis[i][j]) break;
            ret[3] += board[i][j];
        }
    }

    // 4번 선거구
    for (int i = x + d2 + 1; i <= n; ++i) {
        for (int j = n; j >= y - d1 + d2; --j) {
            if (vis[i][j]) break;
            ret[4] += board[i][j];
        }
    }

    ret[5] = total_sum - accumulate(ret + 1, ret + 5, 0);
    answer = min(answer, *max_element(ret + 1, ret + 6) - *min_element(ret + 1, ret + 6));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= n; ++y) {
            cin >> board[x][y];
            total_sum += board[x][y];
        }
    
    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= n; ++y)
            for (int d1 = 1; d1 <= n; ++d1)
                for (int d2 = 1; d2 <= n; ++d2) {
                    if (x + d1 + d2 > n) continue;
                    if (y - d1 < 1) continue;
                    if (y + d2 > n) continue;
                    calculate(x, y, d1, d2);
                }

    cout << answer << "\n";

    return 0;
}