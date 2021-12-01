#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        int n, m; cin >> n >> m;
        assert(m < n);

        bool flag[100001];
        memset(flag, true, sizeof(flag));
        for (int i = 0; i < m; ++i) {
            int x, y; cin >> y >> x >> y;
            flag[x] = false;
        }

        int root = -1;
        for (int i = 1; i <= n; ++i)
            if (flag[i]) {
                root = i;
                break;
            }

        for (int i = 1; i <= n; ++i) {
            if (i == root) continue;
            else cout << root << " " << i << "\n";
        }
    }
    return 0;
}