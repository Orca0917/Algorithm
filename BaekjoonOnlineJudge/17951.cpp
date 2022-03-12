#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;
    vector<int> tests(n);
    for (int &score : tests) cin >> score;

    auto in_condition = [&](const int mid) -> bool {
        int part = 0;

        int sum = 0;
        for (int score : tests) {
            sum += score;
            if (sum >= mid) {
                sum = 0;
                ++part;
            }

            if (part >= k) return true;
        }

        return false;
    };

    int lo = 0, hi = 20 * 1e5, answer = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (in_condition(mid)) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << answer << "\n";
    return 0;
}