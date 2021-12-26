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
        vector<int> a(n);
        for (int &e : a) cin >> e;

        int ans = 1;
        bool died = false;

        for (int i = 0; i < n && !died; ++i) {
            if (a[i] == 0) {
                if (i > 0 && a[i - 1] == 0) died = true;;
            } else {
                if (i > 0 && a[i - 1] == 1) ans += 5;
                else ans += 1;
            }
        }

        if (died) cout << "-1\n";
        else cout << ans << "\n";
    }
        
    return 0;
}