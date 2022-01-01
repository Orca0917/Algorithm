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
        int n, l, r; cin >> n >> l >> r;
        vector<int> A(n);
        for (int &a : A) cin >> a;
        sort(A.begin(), A.end());

        ll answer = 0;
        for (int i = 0; i < n; ++i) {
            answer += upper_bound(A.begin(), A.end(), r - A[i]) - A.begin();
            answer -= lower_bound(A.begin(), A.end(), l - A[i]) - A.begin();
            if (l <= 2 * A[i] && 2 * A[i] <= r) --answer;
        }

        cout << answer / 2 << "\n";
    }
    
    return 0;
}
