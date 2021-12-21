#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

int n; // 세계의 크기 (n x n)
int k; // 문명 발상지 수 (~100,000)
int board[2001][2001];

int uniqueNumber = 1;
int movement[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool vis[2001][2001];

// 문명 발상지의 위치
vector<pii> civils;

vector<int> parent(100001), height(100001, 0);

// 문명이 현재 마지막까지 퍼진 위치
queue<pii> q;

int find_func(int x) {
    if (x == parent[x]) return x;
    else return parent[x] = find_func(parent[x]);
}

void union_func(int x, int y) {
    x = find_func(x), y = find_func(y);
    if (x == y) return;
    if (height[x] > height[y]) swap(x, y);
    parent[x] = y;
    if (height[x] == height[y]) ++height[y];
}

void spreadCivils() {
    int qSize = q.size();

    while (qSize--) {
        int hereX = q.front().first;
        int hereY = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int thereX = hereX + movement[i][0];
            int thereY = hereY + movement[i][1];

            if (thereX < 1 || thereX > n || thereY < 1 || thereY > n) continue; // 범위를 벗어나는 경우 제외

            if (vis[thereX][thereY]) continue;

            vis[thereX][thereY] = true;
            q.push({thereX, thereY});
            board[thereX][thereY] = board[hereX][hereY];

            for (int j = 0; j < 4; ++j) {
                int nearX = thereX + movement[j][0];
                int nearY = thereY + movement[j][1];

                if (nearX < 1 || nearX > n || nearY < 1 || nearY > n) continue;
                if (board[nearX][nearY] == board[thereX][thereY]) continue;
                
                if (board[nearX][nearY] != -1 && find_func(board[nearX][nearY]) != find_func(board[thereX][thereY])) {
                    union_func(board[nearX][nearY], board[thereX][thereY]);
                    break;
                }
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;

    memset(board, -1, sizeof(board));
    memset(vis, false, sizeof(vis));
    iota(parent.begin(), parent.end(), 0);

    civils.resize(k);
    for (int i = 0; i < k; ++i) {
        int posx, posy; cin >> posx >> posy;

        civils[i] = {posx, posy};
        board[posx][posy] = uniqueNumber++;
        
        for (int j = 0; j < 4; ++j) {
            int nx = posx + movement[j][0];
            int ny = posy + movement[j][1];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
            if (board[nx][ny] != -1) {
                union_func(board[posx][posy], board[nx][ny]);
            }
        }
        q.push({posx, posy});
    }

    int passedYear = 0;
    while (true) {

        // 모든 문명이 동일한 문명에 있는지 확인한다.
        bool allSameCivils = true;
        int x = civils[0].first, y = civils[0].second;
        for (int i = 1; i < k && allSameCivils; ++i) {
            int x1 = civils[i].first, y1 = civils[i].second;
            if (find_func(board[x][y]) != find_func(board[x1][y1]))
                allSameCivils = false;
        }

        // 종료시점: 모든 문명이 하나의 문명인 경우
        if (allSameCivils) break;

        // 각 문명을 전파 시킨다.
        spreadCivils();
        ++passedYear;
    }

    cout << passedYear << "\n";

    return 0;
}