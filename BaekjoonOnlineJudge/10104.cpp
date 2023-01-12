#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<int> v(n), alive(n, true);
    for (int i = 0; i < n; ++i) v[i] = i + 1;

    while (m--) {
        int k; cin >> k;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (alive[i]) ++cnt;
            if (cnt % k == 0) {
                alive[i] = false;
                cnt = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (alive[i]) cout << i + 1 << "\n";
    }
    
    
    return 0;
}