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
        vector<ll> v(n);
        for (ll &x: v) cin >> x;
        sort(v.begin(), v.end());

        ll sum = 0, ans = v.back();
        for (int i = 1; i < n; ++i) {
            sum += v[i];
            ans += sum - (1LL * v[i] * (i + 1));
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}