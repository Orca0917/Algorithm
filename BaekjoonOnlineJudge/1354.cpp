#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;
ll n, p, q, x, y;

map<ll, ll> m;

ll dp(ll val) {
    if (val <= 0) return 1;
    if (m.find(val) != m.end()) return m[val];

    return m[val] = dp(val / p - x) + dp(val / q - y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> p >> q >> x >> y;

    cout << dp(n) << "\n";
    return 0;
}