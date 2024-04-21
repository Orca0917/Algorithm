#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, M, L; cin >> N >> M >> L;

    vector<int> cake(M);
    for (int &e : cake) cin >> e;
    cake.push_back(L);

    while (N--) {
        int threshold; cin >> threshold;
        int lo = 0;
        int hi = L;
        int answer = lo;

        auto is_possible = [cake, threshold](int mid) -> bool {
            int val = mid;
            for (int i = 0; i <= threshold; ++i) {
                auto it = lower_bound(cake.begin(), cake.end(), val);
                if (it == cake.end()) return false;
                val = *it + mid;
            }
            return true;
        };

        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (is_possible(mid)) {
                answer = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        cout << answer << "\n";
    }
    
    return 0;
}