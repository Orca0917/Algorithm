#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct tri {
    int start, end, interval;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k, d; cin >> n >> k >> d;

    vector<tri> v(k);
    for (tri &e : v) cin >> e.start >> e.end >> e.interval;

    auto is_possible = [&](const int mid) -> bool {
        ll box_number = 0;
        for (tri e : v) {
            if (mid < e.start) continue;
            int val = min(mid, e.end) - e.start;
            box_number += 1LL * (val / e.interval + 1);
        }
        return box_number >= 1LL * d;
    };

    int lo = 1, hi = n, answer = 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

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