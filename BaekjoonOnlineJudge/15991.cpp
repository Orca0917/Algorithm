#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

ll memo[100001];

ll dp(int n) {
    if (n <= 5) return n / 2 + 1;

    ll &ret = memo[n];
    if (ret != -1) return ret;

    ret = dp(n - 2) + dp(n - 4) + dp(n - 6);
    ret %= 1'000'000'009;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << dp(n) << "\n";
    }
    
    return 0;
}