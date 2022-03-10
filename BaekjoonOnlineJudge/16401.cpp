#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n;
    int m; cin >> n >> m;
    vector<int> snack(m);
    for (int &e: snack) cin >> e;

    auto can_give = [&](const int len) -> bool {
        ll cnt = 0;
        for (int s : snack) {
            cnt += s / len;
        }

        return cnt >= n;
    };

    int lo = 1, hi = 1000000000, answer = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (can_give(mid)) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << answer << "\n";
    return 0;
}