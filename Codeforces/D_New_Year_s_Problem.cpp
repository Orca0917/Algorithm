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
        int m, n; // 상점의 수, 친구의 수
        cin >> m >> n;

        vector<vector<int> > P;
        P.resize(m);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int joy; cin >> joy;
                P[i].push_back(joy);
            }
        }

        int lo = 1, hi = 1e9 + 1;
        auto check = [&](int x) {
            vector<bool> able(n, false);
            bool pair = false;
            for (int i = 0; i < m; ++i) {
                int cnt = 0;
                for (int j = 0; j < n; ++j) {
                    if (P[i][j] >= x) {
                        able[j] = true;
                        ++cnt;
                    }
                }

                // 최소 2개 이상 구매할 수 있는 상점이 있어야 한다.
                if (cnt > 1) pair = true;
            }

            // 최소 2개 이상 구매할 수 없고, 인원은 2명 이상인 경우
            if (!pair && n > 1) return false;

            // 모든 인원이 구매할 수 있어야 한다.
            bool ret = true;
            for (bool b : able) ret = ret && b;
            return ret;
        };

        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            
            if (check(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        cout << lo << "\n";
    }
       
    return 0;
}