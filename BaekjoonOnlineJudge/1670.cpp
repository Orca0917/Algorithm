#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MOD 987654321
using namespace std;

int n;
ll memo[10001];

ll dp(int x) {
    if (x <= 2) return 1;

    ll &ret = memo[x];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0; i <= (x - 2); i += 2) {
        ret += dp(i) * dp(x - 2 - i);
        ret %= MOD;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    memset(memo, -1, sizeof(memo));
    cout << dp(n);
    
    return 0;
}