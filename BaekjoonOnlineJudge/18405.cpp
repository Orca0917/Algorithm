#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int s, target_x, target_y, n, k;
int board[201][201];
int movement[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
priority_queue<tuple<int, int, int, int>> pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> k;
    memset(board, 0, sizeof(board));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            if (board[i][j] != 0) {
                pq.push({0, -board[i][j], i, j});
            }   
        }

    cin >> s >> target_x >> target_y;

    int virus, x, y, t;
    while (!pq.empty()) {
        tie(t, virus, x, y) = pq.top(); pq.pop();
        t *= -1;
        virus *= -1;

        if (t == s) break;

        for (int i = 0; i < 4; ++i) {
            int xx = x + movement[i][0];
            int yy = y + movement[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
            if (board[xx][yy] != 0) continue;

            board[xx][yy] = virus;
            pq.push({-(t + 1), -virus, xx, yy});
        }
    }

    cout << board[target_x - 1][target_y - 1] << "\n";
    
    return 0;
}