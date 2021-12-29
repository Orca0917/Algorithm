#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<int> H(n);
        for (int &h : H) cin >> h;

        auto check = [n, H](const int x) -> bool {
            // 연산에 사용하기 위한 복사본 생성
            vector<int> P = H;

            for (int i = n - 1; i >= 2; --i) {
                if (P[i] < x) return false;

                // 앞, 앞앞 주머니에 줄 수 있는 조약돌 수
                int extra = min(P[i] - x, H[i]);
                int d = extra / 3;

                P[i - 2] += 2 * d;
                P[i - 1] += d;
                P[i] -= 3 * d;
            }

            for (int i = 0; i < n; ++i) if (P[i] < x) return false;

            return true;
        };

        int lo = 1, hi = 1e9;
        int ans = 1;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            // cout << "mid = " << mid << " >> " << check(mid, H) << "\n";
            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        cout << ans << "\n";
    }
    
    return 0;
}