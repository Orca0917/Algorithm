#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, d;
int movement[3][2] = {{0, -1}, {-1, 0}, {0, 1}};
int origin_board[17][16];
int board[17][16];
set<pii> eraser;
int answer = 0, enemy_cnt = 0;


int bfs(int sx, int sy) {
    queue<tuple<int, int, int>> q;
    q.push({sx, sy, 0});

    vector<pii> candi;
    int max_dist = 1e9;

    int x, y, c, ret = 0;
    while (!q.empty()) {
        tie(x, y, c) = q.front(); q.pop();

        // 적 발견
        if (board[x][y] == 1 && c <= max_dist) { 
            if (max_dist > c) candi.clear();
            candi.push_back({x, y});
            max_dist = c;
            continue;
        }

        for (int i = 0; i < 3; ++i) {
            int xx = x + movement[i][0];
            int yy = y + movement[i][1];
            int cc = c + 1;

            if (xx < 1 || xx >= sx || yy < 1 || yy > m) continue;
            if (cc > d) continue;
            q.push({xx, yy, cc});
        }
    }
    
    if (candi.empty()) return 0;

    sort (candi.begin(), candi.end(), [](pii &a, pii &b) {
        if (a.second == b.second) return a.first > b.first;
        return a.second < b.second;
    });
    eraser.insert({candi[0].first, candi[0].second});

    return 1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> d;

    // 적의 정보 입력
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> origin_board[i][j];

    // 조합 생성
    vector<int> perm(m, 0);
    perm[0] = perm[1] = perm[2] = 1;


    do {
        // 초기화
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                board[i][j] = origin_board[i][j];

        int row = n + 1;
        int result = 0;
        while (row > 1) {
            for (int j = 0; j < m; ++j) if (perm[j]) bfs(row, j + 1);
            for (pii e : eraser) board[e.first][e.second] = 0;
            result += eraser.size();
            eraser.clear();

            --row;
            for (int j = 1; j <= m; ++j) board[row][j] = 0;
        }

        // BFS 탐색
        answer = max(answer, result);

    } while (next_permutation(perm.rbegin(), perm.rend()));

    cout << answer << "\n";

    return 0;
}