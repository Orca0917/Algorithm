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
        int n, q; cin >> n >> q;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> answer(n, 0);
        int cur_iq = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] <= cur_iq) answer[i] = 1;
            else if (cur_iq < q) {
                ++cur_iq;
                answer[i] = 1;
            }
            else answer[i] = 0;
        }

        for (int i = 0; i < n; ++i) cout << answer[i];
        cout << "\n";
    }

    return 0;
}