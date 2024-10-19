#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;

int psum[1025][1025];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    
    memset(psum, 0, sizeof(psum));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int value; cin >> value;
            psum[i][j] = psum[i][j - 1] + psum[i - 1][j] - psum[i - 1][j - 1] + value;
        }
    }

    int q; cin >> q;
    while (q--) {
        int srcx, srcy, dstx, dsty;
        cin >> srcx >> srcy >> dstx >> dsty;

        cout << psum[dstx][dsty] - psum[srcx - 1][dsty] - psum[dstx][srcy - 1] + psum[srcx - 1][srcy - 1] << "\n";
    }
    
    return 0;
}