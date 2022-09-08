#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Q {
    int x;
    int y;
    int l;
    int r;
};

int n, m, l, r;
int board[1001][1001];
bool vis[1001][1001];

int start_x, start_y;
int result = 0;

queue<Q> q;

void enqueue(int X, int Y, int L, int R) {
    q.push({X, Y, L, R});
    vis[X][Y] = true;
}


void bfs() {

    q.push({start_x, start_y, l, r});
    vis[start_x][start_y] = true;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int left = q.front().l;
        int right = q.front().r;
        q.pop();

        ++result;

        // go up
        for (int i = x - 1; i >= 0 && board[i][y] == 0 && !vis[i][y]; --i) enqueue(i, y, left, right);

        // go down
        for (int i = x + 1; i < n && board[i][y] == 0 && !vis[i][y]; ++i) enqueue(i, y, left, right);

        // go left
        if (left == 0 || y - 1 < 0 || vis[x][y - 1] || board[x][y - 1] == 1) ;
        else enqueue(x, y - 1, left - 1, right);

        // go right
        if (right == 0 || y + 1 >= m || vis[x][y + 1] || board[x][y + 1] == 1) ;
        else enqueue(x, y + 1, left, right - 1);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(vis, false, sizeof(vis));

    cin >> n >> m >> l >> r;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            int ic = c - '0';

            board[i][j] = ic;

            if (ic == 2) {
                start_x = i;
                start_y = j;
            }
        }
    }

    bfs();

    cout << result << "\n";
    
    return 0;
}