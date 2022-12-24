#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

char board[101][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> board[i][j];

    int ans1 = 0, ans2 = 0, temp = 0;
    for (int i = 0; i < n; ++i) {
        temp = 0;
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == 'X') {
                if (temp >= 2) ans1 += 1;
                temp = 0;
            } else {
                temp += 1;
            }
        }
        if (temp >= 2) ans1 += 1;
    }

    for (int i = 0; i < n; ++i) {
        temp = 0;
        for (int j = 0; j < n; ++j) {
            if (board[j][i] == 'X') {
                if (temp >= 2) ans2 += 1;
                temp = 0;
            } else {
                temp += 1;
            }
        }
        if (temp >= 2) ans2 += 1;
    }

    cout << ans1 << " " << ans2 << "\n";
    
    return 0;
}