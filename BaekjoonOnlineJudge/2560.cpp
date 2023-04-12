#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MOD 1000

using namespace std;

int a, b, d, n;
int memo[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> a >> b >> d >> n;
    
    memset(memo, 0, sizeof(memo));
    for (int day = 0; day < a; ++day) memo[day] = 1;
    for (int day = a; day <= n; ++day) {
        memo[day] = (memo[day - 1] + memo[day - a]) % MOD;
        if (day >= b) memo[day] = (memo[day] - memo[day - b] + MOD) % MOD;
    }

    if (n - d >= 0) cout << (memo[n] - memo[n - d] + MOD) % MOD << "\n";
    else cout << memo[n] << "\n";

    return 0;
}