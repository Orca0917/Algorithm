#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

#define EMPTY 0
#define WALL 1
#define VIRUS 2

using namespace std;

struct Q {
    int x;
    int y;
    int move_cnt;
};

int board[51][51];
bool vis[51][51];
int movement[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

vector<bool> virus_mask;
vector<pii> virus_pos;
queue<Q> q;

int n, virus_cnt;

bool has_spread_all() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == EMPTY && !vis[i][j]) return false;
        }
    }
    return true;
}


int spread_virus() {
    memset(vis, false, sizeof(vis));

    int ret = 0;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int cnt = q.front().move_cnt;
        q.pop();

        if (board[x][y] == EMPTY) ret = max(ret, cnt);

        for (int i = 0; i < 4; ++i) {
            int xx = x + movement[i][0];
            int yy = y + movement[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
            if (board[xx][yy] == WALL || vis[xx][yy]) continue;

            vis[xx][yy] = true;
            q.push({xx, yy, cnt + 1});
        }
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> virus_cnt;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int &cell = board[i][j];
            cin >> cell;
            if (cell == VIRUS) virus_pos.push_back({i, j});
        }
    }

    int total_virus = (int)virus_pos.size();
    virus_mask.resize(total_virus, false);

    for (int i = 0; i < virus_cnt; ++i) virus_mask[i] = true;

    int answer = 1e9;

    do {
        for (int i = 0; i < total_virus; ++i)
            if (virus_mask[i])
                q.push({virus_pos[i].first, virus_pos[i].second, 0});

        int res = spread_virus();
        if (has_spread_all() == false) res = 1e9; 
        answer = min(answer, res);

    } while (next_permutation(virus_mask.rbegin(), virus_mask.rend()));

    cout << (answer == 1e9 ? -1 : answer) << "\n";
    
    return 0;
}