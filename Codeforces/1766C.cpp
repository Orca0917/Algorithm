#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool vis[2][200001];
string s[2];
int n;

bool go(int x, int y) {

    while (y < n) {
        if (s[x ^ 1][y] == 'B' && !vis[x ^ 1][y]) {
            x ^= 1;
            vis[x][y] = true;
        }

        else if (y + 1 < n && s[x][y + 1] == 'B') {
            ++y;
            vis[x][y] = true;
        }

        else
            break;
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            if (s[i][j] == 'B' && vis[i][j] == false) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        cin >> n;
        cin >> s[0] >> s[1];

        bool ret1 = false;
        bool ret2 = false;

        memset(vis, false, sizeof(vis));
        if (s[0][0] == 'B') {
            vis[0][0] = true;
            ret1 = go(0, 0);
        }

        memset(vis, false, sizeof(vis));
        if (s[1][0] == 'B') {
            vis[1][0] = true;
            ret2 = go(1, 0);
        }

        
        if (ret1 || ret2) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}