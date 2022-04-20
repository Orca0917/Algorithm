#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1'000'000'007
using namespace std;

vector<ll> factorial(2000001, 1);
ll inverse(int n) {
    ll x = n, y = MOD - 2, result = 1;
    while (y) {
        if (y % 2) result = result * x % MOD;
        x = x * x % MOD;
        y /= 2;
    }
    return result;
}
ll combination(int n, int r) {
    ll ret = factorial[n] * inverse(factorial[r]) % MOD;
    return ret * inverse(factorial[n - r]) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (int i = 1; i < 2000001; ++i) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        cout << combination(2 * n, n) * inverse(n + 1) % MOD << "\n";

    }
    
    return 0;
}