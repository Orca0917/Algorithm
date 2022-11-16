/**
 * Ref : https://ongveloper.tistory.com/169
*/

#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int dp[1'000'001][2];
int cnt[1'000'001][2];
int n, k;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;    
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        cnt[i % k][x % 2] += 1;
    }

    dp[0][0] = cnt[0][1];
    dp[0][1] = cnt[0][0];

    for (int i = 1; i < k; ++i) {
        dp[i][0] = min(dp[i - 1][1] + cnt[i][0], dp[i - 1][0] + cnt[i][1]);
        dp[i][1] = min(dp[i - 1][1] + cnt[i][1], dp[i - 1][0] + cnt[i][0]);
    }
    cout << dp[k - 1][0];

    return 0;
}