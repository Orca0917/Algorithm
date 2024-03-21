#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
char board[11][11];

void rotate90() {

    for (int i = 0; i < max(n, m); ++i)
        for (int j = i; j < max(n, m); ++j)
            swap(board[i][j], board[j][i]);

    swap(n, m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m / 2; ++j)
            swap(board[i][j], board[i][m - j - 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    int degree; cin >> degree;
    degree %= 360;
    int deg90 = degree / 90;
    int deg45 = degree % 90;

    while (deg90--) rotate90();

    if (deg45) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i - 1; ++j) cout << " ";
            for (int j = 0; j <= min(i, m - 1); ++j) {
                cout << board[i - j][j];
                if (j < min(i, m - 1)) cout << " ";
            }
            cout << "\n";
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < i; ++j) cout << " ";
            for (int j = i; j < min(m, i + n); ++j) {
                cout << board[n - 1 - j + i][j];
                if (j != min(m, i + n) - 1) cout << " ";
            }
            cout << "\n";
        }
                
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << board[i][j];
            cout << "\n";
        }
    }       
    
    return 0;
}