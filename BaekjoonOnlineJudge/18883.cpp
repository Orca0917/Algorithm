#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    int cnt = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << cnt++;
            if (j != m - 1) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}