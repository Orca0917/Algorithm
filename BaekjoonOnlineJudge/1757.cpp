#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int dist[10001];
int memo[10001][501];
int n, m;

int dp(int now_minute, int tired) {
    if (now_minute == n + 1) {
        if (tired == 0) return 0;
        else return -1e7;
    }

    int &ret = memo[now_minute][tired];
    if (ret != -1) return ret;

    ret = -1e7;

    // 휴식
    if (tired == 0) ret = max(ret, dp(now_minute + 1, 0));
    else if (now_minute + tired <= n + 1) ret = max(ret, dp(now_minute + tired, 0));
    
    // 달리기
    if (tired + 1 <= m) ret = max(ret, dp(now_minute + 1, tired + 1) + dist[now_minute]);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> dist[i];

    memset(memo, -1, sizeof(memo));
    cout << dp(1, 0) << "\n";
    
    return 0;
}