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
        int n, m; cin >> n >> m;
        vector<int> a(n), b(m);
        for (int &e : a) cin >> e;
        for (int &e : b) cin >> e;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        ll answer = 0;
        for (int i = n - 1; i >= 0; --i) {
            auto it = lower_bound(b.begin(), b.end(), a[i]);
            int cnt = (it - b.begin());
            if (cnt == 0) break; 
            answer += cnt;
        }

        cout << answer << "\n";
    }
    
    return 0;
}