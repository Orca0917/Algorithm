#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, k;
int board[1010][1010];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> k;

    memset(board, 0, sizeof(board));

    // 광물 정보 입력받기
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> board[i][j];
        }
    }

    auto possible = [&](const int mid) -> bool {
        bool vis[1010][1010];
        memset(vis, false, sizeof(vis));
        int cnt = 0;

        queue<pii> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nx = x + ("0112"[i] - '0') - 1;
                int ny = y + ("1201"[i] - '0') - 1;

                // 테두리를 포함해서 맵 밖으로 벗어나는 경우 pass
                if (nx < 0 || nx > n || ny < 0 || ny > m + 1) continue;

                // 현재 강도보다 높거나 이미 방문한 곳이라면 pass
                if (board[nx][ny] > mid || vis[nx][ny]) continue;

                vis[nx][ny] = true;
                q.push({nx, ny});

                if (board[nx][ny] >= 1) ++cnt;
            }
        }

        return cnt >= k;
    };

    // 이분탐색 실행 -> 채굴기의 강도 설정하기
    int lo = 1, hi = 1e6, answer = 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (possible(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}