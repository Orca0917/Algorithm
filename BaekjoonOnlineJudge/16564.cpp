#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n, k; cin >> n >> k;

    vector<int> X(n);
    for (int &e: X) cin >> e;
    
    int lo = *min_element(X.begin(), X.end());
    int hi = (1e9) + 1e9 / 3;
    int answer = lo;

    auto is_possible = [X, k](int mid) -> bool {
        ll need = 0;
        for (int e : X) need += max(0, mid - e);
        return need <= k;
    };

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (is_possible(mid)) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << answer << "\n";

    return 0;
}