#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, day = 0;
int x[1001][1001];
bool vis[1001][1001];
queue<pii> q;

void bfs() {
    int qs = q.size();

    while (qs--) {
        pii here = q.front(); q.pop();

        for (int i = 0; i < 4; ++i) {
           int tx = here.first + "2110"[i] - '1';
           int ty = here.second + "1021"[i] - '1';
           if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
           if (x[tx][ty] == -1 || vis[tx][ty]) continue;
           vis[tx][ty] = true;
           q.emplace(tx, ty);
        }
    }
}

bool check() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (x[i][j] == 0 && vis[i][j] == false) return true;
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(vis, false, sizeof(vis));

    cin >> m >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> x[i][j];
            if (x[i][j] == 1) {
                q.emplace(i, j);
                vis[i][j] = true;
            }
        }

    bfs();
    while (!q.empty()) {
        ++day;
        bfs();
    }
    
    if (check()) cout << "-1\n";
    else cout << day << "\n";
    
    return 0;
}