#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ull n; cin >> n;
    ull answer = 0;
    ull low = 0, hi = (1ULL << 32);

    while (low <= hi && n > 0) {
        ull mid = (low + hi) / 2ULL;
        ull val = 1ULL * mid * mid;
        // cout << mid << ", " << val << "\n";
        if (val >= n) {
            answer = mid;
            hi = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}