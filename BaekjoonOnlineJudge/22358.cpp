#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m, k, s, t;

ll memo[100001][11];
vector<pair<int, ll>> up[100001], down[100001];

ll dp(int cur, int lift) {
    if (lift == 0 && cur == t) return 0;
    else if (lift == 0 && t < cur) return -1e18;

    ll &ret = memo[cur][lift]; 
    if (ret != -1) return ret;

    // 리프트를 타는 경우
    ret = -1e18;

    if (lift > 0)
        for (pii e : up[cur])
            ret = max(ret, dp(e.first, lift - 1));

    // 내려가는 경우
    for (pii e : down[cur]) ret = max(ret, dp(e.first, lift) + e.second);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> k >> s >> t;
    for (int i = 0; i < m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        down[u].push_back({v, c});
        up[v].push_back({u, 0});
    }

    memset(memo, -1LL, sizeof(memo));
    ll result = dp(s, k);
    if (result < 0) cout << "-1\n";
    else cout << result << "\n";

    return 0;
}