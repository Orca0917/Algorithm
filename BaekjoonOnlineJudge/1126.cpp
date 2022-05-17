#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define INF 1234567

using namespace std;

int memo[51][250001];
vector<int> blocks;

int dp(int idx, int diff) {
    
    // outliers
    if (diff > 250000 || diff < 0) return -INF;
    if (idx == -1 && diff) return -INF;

    // terminate condition
    if (idx == -1 && diff == 0) return 0;

    int &ret = memo[idx][diff];
    if (ret != -1) return ret;

    // default
    ret = dp(idx - 1, diff);
    ret = max(ret, dp(idx - 1, diff + blocks[idx]));
    ret = max(ret, dp(idx - 1, diff - blocks[idx]) + blocks[idx]);
    ret = max(ret, dp(idx - 1, blocks[idx] - diff) + diff);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    blocks.resize(n);

    for (int &e: blocks) cin >> e;

    memset(memo, -1, sizeof(memo));

    int answer = dp(n - 1, 0);
    
    if (answer <= 0) answer = -1;
    cout << answer << "\n";

    return 0;
}