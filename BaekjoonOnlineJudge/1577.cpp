#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 세로
int M; // 가로
int K; // 공사구간의 수

ll memo[101][101];
vector<pii> construction[101][101];

ll dp(int x, int y) {
    if (x == N && y == M) return 1;

    ll &ret = memo[x][y];
    if (ret != -1) return ret;

    ret = 0;
    if (x < N) {
        bool is_possible = true;
        for (pii e : construction[x][y]) if (e.first == x + 1 && e.second == y) is_possible = false;
        for (pii e : construction[x + 1][y]) if (e.first == x && e.second == y) is_possible = false;
        if (is_possible) ret += dp(x + 1, y);
    }
    if (y < M) {
        bool is_possible = true;
        for (pii e : construction[x][y]) if (e.first == x && e.second == y + 1) is_possible = false;
        for (pii e : construction[x][y + 1]) if (e.first == x && e.second == y) is_possible = false;
        if (is_possible) ret += dp(x, y + 1);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));

    cin >> N >> M >> K;
    while (K--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        construction[a][b].push_back({c, d});
        construction[c][d].push_back({a, b});
    }

    cout << dp(0, 0) << "\n";
    return 0;
}