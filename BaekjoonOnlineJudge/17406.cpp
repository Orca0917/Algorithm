#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Operation {
    int r, c, s;
};

int n, m, k;
int board[51][51];
int origin[51][51];
vector<Operation> ops;
vector<int> perm;

void copy_board() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            board[i][j] = origin[i][j];
}

void rotation(int r, int c, int s) {
    int ret[51][51];
    int ss = s;
    while (s >= 1) {
        int x = r - s;
        int y = c - s + 1;
        
        for (int i = 0; i < 2 * s; ++i) {
            ret[r - s][c - s + i + 1] = board[r - s][c - s + i];
            ret[r - s + i + 1][c + s] = board[r - s + i][c + s];
            ret[r + s][c + s - i - 1] = board[r + s][c + s - i];
            ret[r + s - i - 1][c - s] = board[r + s - i][c - s];
        }

        --s;
    }

    for (int i = r - ss; i <= r + ss; ++i)
        for (int j = c - ss; j <= c + ss; ++j) {
            if (i == r && j == c) continue;
            board[i][j] = ret[i][j];
        }
}


int get_min_sum() {
    int ret = 1e9;
    for (int i = 1; i <= n; ++i) {
        ret = min(ret, accumulate(board[i] + 1, board[i] + m + 1, 0));
    }
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> origin[i][j];
        
    ops.resize(k);
    perm.resize(k);
    for (int i = 0; i < k; ++i) perm[i] = i;
    for (Operation &e : ops) {
        cin >> e.r >> e.c >> e.s;
    }

    int answer = 1e9;
    do {
        copy_board();

        for (int i = 0; i < k; ++i)
            rotation(ops[perm[i]].r, ops[perm[i]].c, ops[perm[i]].s);
            
        answer = min(get_min_sum(), answer);

    } while (next_permutation(perm.begin(), perm.end()));

    cout << answer << "\n";
    
    return 0;
}