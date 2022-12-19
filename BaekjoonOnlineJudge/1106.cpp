#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define INF 1e9

using namespace std;

int c, n;
pii city[21];

int memo[21][1001];

int dp(int index, int target) {
    if (target <= 0) return 0;
    if (index == n + 1) return INF;

    int &ret = memo[index][target];
    if (ret != -1) return ret;

    ret = INF;
    for (int i = 0; i * city[index].second < target + city[index].second; ++i) {
        ret = min(ret, dp(index + 1, target - i * city[index].second) + i * city[index].first);
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> c >> n;
    for (int i = 1; i <= n; ++i) cin >> city[i].first >> city[i].second;
    
    memset(memo, -1, sizeof(memo));
    cout << dp(1, c) << "\n";

    return 0;
}