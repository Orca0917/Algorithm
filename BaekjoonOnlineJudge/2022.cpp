#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    double x, y, c; cin >> x >> y >> c;
    double lo = 0, hi = min(x, y), ans = 0;

    while (abs(hi - lo) > 1e-6) {
        double mid = (lo + hi) / 2.0;
        double height1 = sqrt(x * x - mid * mid);
        double height2 = sqrt(y * y - mid * mid);
        double height = (height1 * height2) / (height1 + height2);

        if (height > c) {
            lo = mid;
            ans = mid;
        } else {
            hi = mid;
        }
    }

    cout << ans << "\n";
    
    return 0;
}