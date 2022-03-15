#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<bool> available(300'001, false);

    // -- Get input
    int n; cin >> n;
    vector<int> v(n);
    for (auto &e : v) cin >> e;

    // -- Gate for parametric search
    auto is_available = [&](const int mid) -> bool {
        int cnt = 0;
        for (int e : v) {
            if (e >= mid) ++cnt;
            else cnt = 0;

            if (cnt == mid) return true;
        }
        return false;
    };

    // -- Parametric Search
    int lo = 1, hi = 1e6, answer = 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (is_available(mid)) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    // -- Print answer
    cout << answer << "\n";

    return 0;
}