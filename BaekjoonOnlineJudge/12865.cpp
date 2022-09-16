#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, k;
int memo[101][100'001];
vector<pii> bag;

int dp(int idx, int available) {
    if (idx == n || available == 0) return 0;

    int &ret = memo[idx][available];
    if (ret != -1) return ret;

    ret = dp(idx + 1, available);

    if (bag[idx].first <= available)
        ret = max(ret, dp(idx + 1, available - bag[idx].first) + bag[idx].second);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;    
    bag.resize(n);
    for (auto &e : bag) cin >> e.first >> e.second;    

    memset(memo, -1, sizeof(memo));
    cout << dp(0, k) << "\n";

    return 0;
}