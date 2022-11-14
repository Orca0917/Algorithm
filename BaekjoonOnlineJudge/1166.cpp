#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

long double n, l, w, h;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cout << fixed;
    cout.precision(11);

    cin >> n >> l >> w >> h;

    auto is_possible = [&](const long double mid) -> bool {
        ll L = floor(l / mid);
        ll W = floor(w / mid);
        ll H = floor(h / mid);

        return L * W * H >= 1LL * n;
    };

    long double lo = 0, hi = 1e9, answer = 0;
    while (lo <= hi) {
        long double mid = (lo + hi) / 2.0;
        if (is_possible(mid)) {
            lo = mid + 1e-10;
            answer = mid;
        } else {
            hi = mid - 1e-10;
        }
    }

    cout << answer << "\n";

    return 0;
}