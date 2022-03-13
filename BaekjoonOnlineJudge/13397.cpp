#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<int> arr(n);
    for (int &e : arr) cin >> e;

    auto is_available = [&](const int mid) -> bool {
        int cnt = 1;
        int mi = arr[0], Ma = arr[0];

        for (int i = 1; i < n; ++i) {
            
            mi = min(mi, arr[i]);
            Ma = max(Ma, arr[i]);

            if (Ma - mi > mid) {
                ++cnt;
                mi = Ma = arr[i];
            }

            if (cnt > m) return false;
        }

        return true;
    };

    int lo = 0, hi = 10000, answer = 0;
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