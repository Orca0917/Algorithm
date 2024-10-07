#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int movement[6][2] = {{-2, -1}, {-2, 1}, {0, -2}, {0, 2}, {2, -1}, {2, 1}};

int bfs(pii src, pii dst, int n) {
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    vis[src.first][src.second] = true;

    queue<pair<pii, int>> q;
    q.push({src, 0});

    while (!q.empty()) {
        pii cur = q.front().first;
        int cnt = q.front().second;
        q.pop();

        if (cur == dst) return cnt;

        for (int i = 0; i < 6; ++i) {
            int nxt_x = cur.first + movement[i][0];
            int nxt_y = cur.second + movement[i][1];

            if (nxt_x < 0 || nxt_y < 0 || nxt_x >= n || nxt_y >= n) continue;
            if (vis[nxt_x][nxt_y]) continue;

            vis[nxt_x][nxt_y] = true;
            q.push({{nxt_x, nxt_y}, cnt + 1});
        }
    }

    return -1;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    
    pii src, dst;
    cin >> src.first >> src.second;
    cin >> dst.first >> dst.second;

    cout << bfs(src, dst, n);

    return 0;
}