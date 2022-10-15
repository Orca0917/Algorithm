#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m, k;
int board[301][301];
int answer[301][301];
vector<int> level[301];

void make_level_vector(int kth) {
    int x = kth, y = kth;

    level[kth].push_back(board[x][y]);
    while (y + 1 < m - kth) level[kth].push_back(board[x][++y]);
    while (x + 1 < n - kth) level[kth].push_back(board[++x][y]);
    while (y - 1 >= kth) level[kth].push_back(board[x][--y]);
    while (x - 1 >= kth) level[kth].push_back(board[--x][y]);
    level[kth].pop_back();
}

void make_answer(int kth) {
    int x = kth, y = kth;
    int sz = level[kth].size();
    int idx = k;
    answer[x][y] = level[kth][idx % sz];
    while (y + 1 < m - kth) answer[x][++y] = level[kth][++idx % sz];
    while (x + 1 < n - kth) answer[++x][y] = level[kth][++idx % sz];
    while (y - 1 >= kth) answer[x][--y] = level[kth][++idx % sz];
    while (x - 1 >= kth) answer[--x][y] = level[kth][++idx % sz];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
        }
    }

    memset(answer, 0, sizeof(answer));
    for (int i = 0; i < ceil(min(n, m) / 2.0); ++i) {
        make_level_vector(i);
        make_answer(i);
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cout << answer[i][j] << " \n"[j == m - 1];
    
    return 0;
}