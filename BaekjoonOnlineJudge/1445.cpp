#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
char board[51][51];
bool vis[51][51];
int movement[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Q {
    int x;
    int y;
    int g;  // garbage
    int ng; // near garbage
};

struct compare {
    bool operator() (const Q &a, const Q &b) {
        if (a.g == b.g) return a.ng > b.ng;
        return a.g > b.g;
    }
};

pii bfs(int sx, int sy) {
    priority_queue<Q, vector<Q>, compare> pq;
    pq.push({sx, sy, 0, 0});
    vis[sx][sy] = true;

    while (!pq.empty()) {
        int x = pq.top().x;
        int y = pq.top().y;
        int g = pq.top().g;
        int ng = pq.top().ng;
        pq.pop();

        if (board[x][y] == 'F') return {g, ng};

        for (int i = 0; i < 4; ++i) {
            int xx = x + movement[i][0];
            int yy = y + movement[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
            if (vis[xx][yy]) continue;
            vis[xx][yy] = true;

            if (board[xx][yy] == 'g') {
                pq.push({xx, yy, g + 1, ng});
            }
            else {
                int ngg = ng;
                if (board[xx][yy] == '.') {
                    for (int j = 0; j < 4; ++j) {
                        int xxx = xx + movement[j][0];
                        int yyy = yy + movement[j][1];
                        if (xxx < 0 || xxx >= n || yyy < 0 || yyy >= m) continue;
                        if (board[xxx][yyy] == 'g') {
                            ++ngg;
                            break;
                        }
                    }
                }
                pq.push({xx, yy, g, ngg});
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    memset(vis, false, sizeof(vis));

    int sx = 0, sy = 0;
    for (int i = 0; i < n; ++i)    
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }

    pii ret = bfs(sx, sy);
    cout << ret.first << " " << ret.second << "\n";

    return 0;
}