#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, r;
int board[101][101];

void horizontal_flip() {
    for (int i = 1; i <= n / 2; ++i)
        for (int j = 1; j <= m; ++j)
            swap(board[i][j], board[n - i + 1][j]);
}

void vertical_flip() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m / 2; ++j)
            swap(board[i][j], board[i][m - j + 1]);
}

void rotate_90() {
    for (int i = 1; i <= max(n, m); ++i)
        for (int j = i; j <= max(n, m); ++j)
            swap(board[i][j], board[j][i]);

    swap(n, m);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m / 2; ++j)
            swap(board[i][j], board[i][m - j + 1]);

}

void rotate_rev90() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m / 2; ++j)
            swap(board[i][j], board[i][m - j + 1]);
    
    for (int i = 1; i <= max(n, m); ++i)
        for (int j = i; j <= max(n, m); ++j)
            swap(board[i][j], board[j][i]);

    swap(n, m);

}

void rotate_quarter() {
    for (int i = 1; i <= n / 2; ++i)
        for (int j = m / 2 + 1; j <= m; ++j)
            swap(board[i][j], board[i + n / 2][j - m / 2]);

    for (int i = 1; i <= n; ++i)
        for (int j = 1 ; j <= m / 2; ++j)
            swap(board[i][j], board[i][j + m / 2]);
}

void rotate_rev_quarter() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1 ; j <= m / 2; ++j)
            swap(board[i][j], board[i][j + m / 2]);

    for (int i = 1; i <= n / 2; ++i)
        for (int j = m / 2 + 1; j <= m; ++j)
            swap(board[i][j], board[i + n / 2][j - m / 2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> r;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> board[i][j];
        }
    }
    
    while (r--) {
        int op; cin >> op;
        if (op == 1) horizontal_flip();
        else if (op == 2) vertical_flip();
        else if (op == 3) rotate_90();
        else if (op == 4) rotate_rev90();
        else if (op == 5) rotate_quarter();
        else if (op == 6) rotate_rev_quarter();
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    
    return 0;
}