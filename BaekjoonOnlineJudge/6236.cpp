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

    auto is_possible = [&](const ll money) -> bool {
        int cnt = 1;
        ll cur = 0;
        for (int cost : v) {
            cur += cost;
            if (cur > money) {
                ++cnt;
                cur = cost;
            }
        }
        return cnt <= m;
    };

    ll lo = *max_element(v.begin(), v.end()), hi = 1e10;
    ll answer = lo;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2LL;
        if (is_possible(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}