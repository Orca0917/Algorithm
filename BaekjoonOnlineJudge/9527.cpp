#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<ll> dp(55);

ll calc(ll value) {
    ll ret = value & 1;
    for (int i = 54; i > 0; --i) {
        if (value & (1LL << i)) {
            ret += dp[i - 1] + (value - (1LL << i) + 1);
            value -= (1LL << i);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    dp[0] = {1};
    for (int i = 1; i < 55; ++i) dp[i] = 2 * dp[i - 1] + (1LL << i);

    ll A, B; cin >> A >> B;
    cout << calc(B) - calc(A - 1) << "\n";
    
    return 0;
}