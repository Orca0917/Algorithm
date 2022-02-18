#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;


struct tri {
    ll jungle = 0;
    ll ocean = 0;
    ll ice = 0;
};

tri psum[1002][1002];
char board[1002][1002];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    int query; cin >> query;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> board[i][j];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            psum[i][j].ice = psum[i - 1][j].ice + psum[i][j - 1].ice - psum[i - 1][j - 1].ice + (int)(board[i][j] == 'I');
            psum[i][j].jungle = psum[i - 1][j].jungle + psum[i][j - 1].jungle - psum[i - 1][j - 1].jungle + (int)(board[i][j] == 'J');
            psum[i][j].ocean = psum[i - 1][j].ocean + psum[i][j - 1].ocean - psum[i - 1][j - 1].ocean + (int)(board[i][j] == 'O');
        }
    }

    while (query--) {
        tri answer;
        int startX, startY, endX, endY; cin >> startX >> startY >> endX >> endY;
        answer.jungle = psum[endX][endY].jungle - psum[endX][startY - 1].jungle - psum[startX - 1][endY].jungle + psum[startX - 1][startY - 1].jungle;
        answer.ocean = psum[endX][endY].ocean - psum[endX][startY - 1].ocean - psum[startX - 1][endY].ocean + psum[startX - 1][startY - 1].ocean;
        answer.ice = psum[endX][endY].ice - psum[endX][startY - 1].ice - psum[startX - 1][endY].ice + psum[startX - 1][startY - 1].ice;
        cout << answer.jungle << " " << answer.ocean << " " << answer.ice << "\n"; 
    }
    return 0;
}