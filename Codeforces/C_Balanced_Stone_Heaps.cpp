#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<ll> H(n);
        for (ll &h : H) cin >> h;

        auto check = [n, H](ll x, vector<ll> P) {

            for (int i = n - 1; i >= 2; --i) {
                if (P[i] < x) return false;
                int extra = min(P[i] - x, H[i]);
                int d = extra / 3;

                P[i - 2] += d * 2;
                P[i - 1] += d;
                P[i] -= 3 * d;
            }

            for (int i = 0; i < n; ++i) if (P[i] < x) return false;
            return true;
        };

        ll lo = 1, hi = 1e9;
        ll ans = 1;

        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            // cout << "mid = " << mid << " >> " << check(mid, H) << "\n";
            if (check(mid, H)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        cout << ans << "\n";
    }
    
    return 0;
}