#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll memo[50];

ll dp(int x) {
    if (x <= 2) return 1;

    ll &ret = memo[x];
    if (ret != -1) return ret;

    ret = dp(x - 2) + dp(x - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    memset(memo, -1, sizeof(memo));
    cout << dp(n) << " " << n - 2 << "\n";
    
    return 0;
}