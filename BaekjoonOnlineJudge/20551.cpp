#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<int> v(n);
    for (int &e : v) cin >> e;
    sort(v.begin(), v.end());

    while (m--) {
        int k; cin >> k;
        auto it = lower_bound(v.begin(), v.end(), k);
        if (it != v.end() && *it == k) cout << it - v.begin() << "\n";
        else cout << -1 << "\n";
    }
    
    return 0;
}