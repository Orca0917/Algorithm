#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Q {
    int x;
    int y;
    int t;
    char p;
};

int n, m, k;
int boss_hp;
int boss_x, boss_y;

queue<Q> q;
map<char, int> attk;

bool vis[1001][1001]['z' - 'a' + 1];
char board[1001][1001];
int movement[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};


int bfs() {
    memset(vis, false, sizeof(vis));

    set<char> s;
    int last_time = 1e9;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int t = q.front().t;
        char p = q.front().p;
        q.pop();

        if (t > last_time) break;

        if (x == boss_x && y == boss_y) {
            boss_hp -= attk[p];
            s.insert(p);
            q.push({x, y, t + 1, p});

            if (boss_hp <= 0 && last_time == 1e9) last_time = t;
        } 
        
        else {
            for (int i = 0; i < 4; ++i) {
                int xx = x + movement[i][0];
                int yy = y + movement[i][1];

                if (xx < 0 || xx >= n || yy < 0 || y >= m) continue;
                if (board[xx][yy] == 'X') continue;
                if (vis[xx][yy][p - 'a']) continue;

                vis[xx][yy][p - 'a'] = true;
                q.push({xx, yy, t + 1, p});
            }
        }
    
    }

    return s.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> k;
    
    memset(vis, false, sizeof(vis));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char &c = board[i][j];
            cin >> c;
            
            if ('a' <= c && c <= 'z') {
                q.push({i, j, 0, c});
                vis[i][j][c - 'a'] = true;
            }
            else if (c == 'B') {
                boss_x = i;
                boss_y = j;
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        char player;
        int atk;
        cin >> player >> atk;
        attk[player] = atk;
    }

    cin >> boss_hp;

    cout << bfs() << "\n";

    return 0;
}