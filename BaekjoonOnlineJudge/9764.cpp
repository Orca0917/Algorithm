#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 100999
using namespace std;

// memo[i][j] : i 를 j 이하의 수들의 합으로 만드는 경우의 수
int memo[2001][2001];

int dp(int n, int k) {
    if (n == 0) return 1;
    else if (n < 0 || k == 0) return 0;

    int &ret = memo[n][k];
    if (ret != -1) return ret;

    ret = 0;
    for (int num = min(n, k); num >= 1; --num) {
        ret += dp(n - num, num - 1);
        ret %= MOD;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));

    int testcase; cin >> testcase;
    while (testcase--) {
        int N; cin >> N;
        cout << dp(N, N - 1) + 1 << "\n";
    }
    
    return 0;
}