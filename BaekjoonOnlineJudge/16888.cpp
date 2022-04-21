#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[1'000'010];

int dp(int n) {
    
    int &ret = memo[n];
    if (ret != -1) return ret;

    for (int i = (int)sqrt(n); i > 0; --i) {
        // 짝수가 존재하면, 무조건 승리
        if (dp(n - i * i) % 2 == 0) {
            return ret = 1;
        }
    }

    return ret = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(memo, -1, sizeof(memo));
    memo[0] = memo[2] = 0;
    memo[1] = 1;

    for (int i = 1; i <= 1'000'000; ++i)
        dp(i);

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        if (memo[n] % 2) cout << "koosaga\n";
        else cout << "cubelover\n";
    }

    return 0;
}