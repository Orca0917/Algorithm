/* 
 * author: 0917jong
 * date: 2021-12-01
 */

#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
bool canSlave(ll mid, ll h, vector<ll> &a) {
    int n = a.size() - 1;
    ll damage = 0;
    for (int i = 0; i < n; ++i) {
        damage += min(a[i + 1] - a[i], mid);
    }
    return damage >= h;
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        ll n, h; cin >> n >> h;
        vector<ll> a(n + 1);
        for (int i = 0; i < n; ++i) cin >> a[i];
        a[n] = 2 * 1e18 + 1;
        ll lo = 1, hi = 1e18;
        ll answer = hi;
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            if (canSlave(mid, h, a)) {
                answer = mid;
                hi = mid - 1;
            }
            else lo = mid + 1;
        }
        cout << answer << "\n";
    }
    return 0;
}