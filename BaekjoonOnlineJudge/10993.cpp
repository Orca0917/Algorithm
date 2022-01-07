#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int len[11] = {0, 1, 5, 13, 29, 61, 125, 253, 509, 1021, 2045};
int height[11] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
char board[3000][3000];

void drawDownTri(int x, int y, int sz);
void drawUpTri(int x, int y, int sz) {
    if (sz == 1) {
        board[x - 1][y] = '*';
        return;
    }

    for (int j = y; j < len[sz] + y; ++j) board[x - 1][j] = '*';

    int l = y + 1, r = len[sz] + y - 2;
    for (int i = x - 2; i >= x - height[sz]; --i) {
        board[i][l] = board[i][r] = '*';
        ++l;
        --r;
    }

    drawDownTri(x - ceil(height[sz] / 2.0), y + ceil(height[sz] / 2.0), sz - 1);
}

void drawDownTri(int x, int y, int sz) {
    for (int j = y; j < len[sz] + y; ++j) board[x][j] = '*';

    int l = y + 1, r = len[sz] + y - 2;
    for (int i = x + 1; i < height[sz] + x; ++i) {
        board[i][l] = board[i][r] = '*';
        ++l;
        --r;
    }

    drawUpTri(x + ceil(height[sz] / 2.0), y + ceil(height[sz] / 2.0), sz - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    if (n % 2) drawUpTri(height[n], 0, n);
    else drawDownTri(0, 0, n);
    
    int M;
    if (n % 2) M = ceil(len[n] / 2.0);
    else M = len[n];

    for (int i = 0; i < height[n]; ++i) {
        for (int j = 0; j < M; ++j) {
            char c = board[i][j];
            if (c == '*') cout << c;
            else cout << " ";
        }
        if (n % 2) ++M;
        else --M;
        cout << "\n";
    }
    return 0;
}

// 1 3 7 15