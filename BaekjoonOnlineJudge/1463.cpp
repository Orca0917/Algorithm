#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[1'000'001];

int dp(int n) {
    if (n == 1) return 0;

    int &ret = memo[n];
    if (ret != -1) return ret;

    ret = 1e9;
    if (n % 3 == 0) ret = min(ret, dp(n / 3) + 1);
    if (n % 2 == 0) ret = min(ret, dp(n / 2) + 1);
    ret = min(ret, dp(n - 1) + 1);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(memo, -1, sizeof(memo));

    int n; cin >> n;
    cout << dp(n) << "\n";

    return 0;
}