#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    int tc = 1;
    while (testcase--) {
        int n; cin >> n;
        vector<int> v1(n), v2(n);
        for (int &e : v1) cin >> e;
        for (int &e : v2) cin >> e;

        sort(v1.begin(), v1.end());
        sort(v2.rbegin(), v2.rend());

        ll answer = 0;
        for (int i = 0; i < n; ++i) answer += 1LL * v1[i] * v2[i];

        cout << "Case #" << tc++ << ": " << answer << "\n";
    }
    
    return 0;
}