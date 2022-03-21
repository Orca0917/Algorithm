#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll get_sum(ll a, ll d, ll n) {
    return ((2LL * a + (n - 1) * d) * n) / 2LL;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll a, d; cin >> a >> d;
    int q; cin >> q;

    while (q--) {
        ll opt, l, r; cin >> opt >> l >> r;
        if (opt == 1) cout << get_sum(a, d, r) - get_sum(a, d, l - 1) << "\n";
        else cout << (l == r ? a + (l - 1) * d : gcd(a, d)) << "\n";
    }
    return 0;
}
