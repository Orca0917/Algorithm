#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

char cur[51][51];
char ans[51][51];

void flip(int x, int y) {
    for (int i = x - 1; i <= x + 1; ++i)
        for (int j = y - 1; j <= y + 1; ++j)
            cur[i][j] ^= ('1' ^ '0');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;

    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> cur[i][j];
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> ans[i][j];

    ll answer = 0;
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < m - 1; ++j) {
            if (cur[i - 1][j - 1] != ans[i - 1][j - 1]) {
                flip(i, j);
                ++answer;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (cur[i][j] != ans[i][j]) {
                answer = -1;
                goto ANS;
            }
        }
    }

ANS:
    cout << answer << "\n";
    
    return 0;
}