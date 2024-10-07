#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m, blanks = 0;
bool vis[51][51];
int board[51][51];
vector<pii> virus_position;
int mv[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int bfs(int bit) {

    memset(vis, false, sizeof(vis));
    
    queue<pair<pii, int>> q;
    int spread = 0;

    for (int i = 0; i < (int)virus_position.size(); ++i) {
        if (bit & (1 << i)) {
            ++spread;
            q.push({virus_position[i], 0});
            vis[virus_position[i].first][virus_position[i].second] = true;
        }
    }


    int _time = 0;

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int c = q.front().second;
        q.pop();

        _time = max(_time, c);

        for (int i = 0; i < 4; ++i) {
            int xx = x + mv[i][0];
            int yy = y + mv[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
            if (vis[xx][yy] || board[xx][yy] == 1) continue;

            vis[xx][yy] = true;
            q.push({{xx, yy}, c + 1});
            ++spread;
        }
    }

    return (spread == blanks ? _time : 1e9);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 2) virus_position.push_back({i, j});
            if (board[i][j] != 1) blanks += 1;
        }
    }

    int answer = 1e9;

    for (int bit = 0; bit < (1 << (int)virus_position.size()); ++bit) {
        if (__builtin_popcount(bit) == m) {
            int result = bfs(bit);
            answer = min(answer, result);
        }
    }
    
    if (answer == 1e9) answer = -1;
    cout << answer;
    
    return 0;
}