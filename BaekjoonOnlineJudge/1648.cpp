// ref1 : glaceyes
// ref2 : jaimenmin

#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 9901

using namespace std;

int n, m;
int memo[15 * 15][1 << 15];

int dp(int index, int status) {
    // base condition
    if (index == n * m && status == 0) return 1;
    if (index >= n * m) return 0;

    // memoization
    int &ret = memo[index][status];
    if (ret != -1) return ret;

    // current block has been occupied
    if (status & 1) ret = dp(index + 1, status >> 1);
    else {

        // set block with size (2x1)
        ret = dp(index + 1, (status >> 1) | (1 << (m - 1)));

        // (not a last col) & (vacant next block) 
        if ((index % m != m - 1) && (status & 2) == 0)
            ret += dp(index + 2, status >> 2);
    }

    return ret = ret % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    memset(memo, -1, sizeof(memo));

    cout << dp(0, 0) << "\n";

    return 0;
}