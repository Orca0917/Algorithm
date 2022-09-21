#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

char board[1001][1001];
int vis[1001][1001];
int n, m;
map<char, pii> movement;


int dfs(int x, int y, int id) {
    if (vis[x][y]) return vis[x][y];
    vis[x][y] = id;

    pii diff = movement[board[x][y]];
    int xx = x + diff.first;
    int yy = y + diff.second;

    return vis[x][y] = dfs(xx, yy, id);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    movement['U'] = {-1, 0};
    movement['D'] = {1, 0};
    movement['L'] = {0, -1};
    movement['R'] = {0, 1};

    cin >> n >> m;
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];


    int id = 1;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int ret = dfs(i, j, id);
            if (ret == id) ++id;
        }
    }

    cout << id - 1 << "\n";
    
    return 0;
}