#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

string solve(map<int, int> &m) {
    for (auto it = m.begin(); it != m.end(); it = next(it)) {
            if (it -> second > n / 2) {
                return to_string(it -> first);
            }
        }
    return "SYJKGW";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        map<int, int> m;
        for (int i = 0; i < n; ++i) {
            int k; cin >> k;
            m[k] += 1;
        }
        
        cout << solve(m);
    }

    
    return 0;
}