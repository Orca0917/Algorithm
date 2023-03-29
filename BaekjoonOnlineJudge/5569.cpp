#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define UP 0
#define RIGHT 1

using namespace std;

int n, m;
int memo[101][101][2];

int dp(int x, int y, int dir) {
    if (x == m && y == n) return 1;
    if (x == m && y == n + 1 && dir == RIGHT) return 1;
    if (x == m + 1 && y == n && dir == UP) return 1;
    if (x > m || y > n) return 0;

    int &ret = memo[x][y][dir];
    if (ret != -1) return ret;

    if (dir == UP) ret = dp(x + 1, y, dir) + dp(x, y + 2, dir ^ 1);
    else ret = dp(x, y + 1, dir) + dp(x + 2, y, dir ^ 1);

    return ret = ret % 100000;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    
    memset(memo, -1, sizeof(memo));
    cout << (dp(1, 2, RIGHT) + dp(2, 1, UP)) % 100000 << "\n";

    return 0;
}