#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<double> v(n);
    for (double &e : v) cin >> e;

    sort(v.begin(), v.end());

    ll answer = 0;
    for (int i = 0; i < n; ++i) {
        double e = v[i];
        auto lo = lower_bound(v.begin(), v.begin() + i, e * 0.9);
        auto hi = upper_bound(v.begin(), v.begin() + i, e);

        answer += distance(lo, hi);
    }

    cout << answer << "\n";
    
    return 0;
}