#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
int board[2222][2222];
int dist[2222][2222];

struct _dtype {
    int cost, x, y;

    // constructor
    _dtype(int cost, int x, int y): cost(cost), x(x), y(y) {}

    // comparable operator
    bool operator < (const _dtype a) const {
        return cost > a.cost;
    }
};

int dijkstra() {

    priority_queue<_dtype> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    while (!pq.empty()) {
        int cost = pq.top().cost;
        int x = pq.top().x;
        int y = pq.top().y;
        pq.pop();

        if (dist[x][y] > cost) continue;

        for (int i = 1; i <= 2; ++i) {
            int nx = x + i % 2;
            int ny = y + i / 2;

            // border
            if (nx == n || ny == n) continue;

            // compare
            int adder = (board[x][y] > board[nx][ny] ? 0 : board[nx][ny] - board[x][y] + 1);
            if (dist[nx][ny] > dist[x][y] + adder) {
                dist[nx][ny] = dist[x][y] + adder;
                pq.push({dist[nx][ny], nx, ny});
            }
        }
    }

    return dist[n-1][n-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    // array information
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            dist[i][j] = 1e9;
        }

    cout << dijkstra();
    
    return 0;
}