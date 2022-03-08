#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<int> v(m);
    for (int &e: v) cin >> e;

    int lo = 1, hi = 1e9;
    int answer = 1;

    auto is_available = [&](const int mid) -> bool {
        int person = 0;
        for (int i = 0; i < m; ++i) {
            person += v[i] / mid;
            if (v[i] % mid != 0) person += 1;
        }
        return person <= n;
    };

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (is_available(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}