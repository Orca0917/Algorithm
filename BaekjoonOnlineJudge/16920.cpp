#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, p;
int stride[10];
int movement[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
char board[1001][1001];

queue<pii> q[10];
vector<int> result(10, 0);


bool check_queue() {
    for (int i = 1; i <= p; ++i) if (!q[i].empty()) return true;
    return false;
}


void bfs() {
    
    while (check_queue()) {
        for (int player = 1; player <= p; ++player) {
            for (int epoch = 0; epoch < stride[player] && !q[player].empty(); ++epoch) {
                int q_size = q[player].size();
                while (q_size--) {
                    int x = q[player].front().first;
                    int y = q[player].front().second;
                    q[player].pop();

                    for (int i = 0; i < 4; ++i) {
                        int xx = x + movement[i][0];
                        int yy = y + movement[i][1];

                        if (xx < 0 || xx >= n || yy < 0 || y >= m) continue;
                        if (board[xx][yy] != '.') continue;

                        board[xx][yy] = player + '0';
                        q[player].push({xx, yy});
                        result[player] += 1;
                    }
                }
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> p;

    for (int i = 1; i <= p; ++i) cin >> stride[i];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char &cell = board[i][j];
            cin >> cell;
            if ('1' <= cell && cell <= '9') {
                int player = cell - '0';
                q[player].push({i, j});
                result[player] += 1;
            }
        }
    }

    bfs();

    for (int i = 1; i <= p; ++i) cout << result[i] << " \n"[i == p];
        
    return 0;
}