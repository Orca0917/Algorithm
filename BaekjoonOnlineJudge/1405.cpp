#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int board[50][50];
bool vis[50][50];
int dir[4];

int n;
double result;

void dfs(int x, int y, int cnt, double prob)
{
    if (cnt == 0)
    {
        result += prob;
        return;
    }

    vis[x][y] = true;
    for (int i = 0; i < 4; ++i)
    {
        int nx = x + "1102"[i] - '0' - 1;
        int ny = y + "2011"[i] - '0' - 1;

        if (vis[nx][ny])
            continue;

        dfs(nx, ny, cnt - 1, prob * (dir[i]) / 100.0);
        vis[nx][ny] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < 4; ++i)
        cin >> dir[i];

    memset(board, 0, sizeof(board));
    memset(vis, false, sizeof(vis));

    dfs(20, 20, n, 1);

    cout << fixed << setprecision(15) << result << "\n";

    return 0;
}