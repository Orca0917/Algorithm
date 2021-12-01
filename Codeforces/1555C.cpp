#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        int m; cin >> m;
        int mat[2][100001], memo[2][100001];
        long long up = 0, down = 0;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < m; ++j) {
                cin >> mat[i][j];
                if (i == 0) up += mat[i][j];
            }
        
        down = 0;
        const long long inf = 1e10;
        long long answer = inf;
        for (int j = 0; j < m; ++j) {
            up -= mat[0][j];
            answer = min(answer, max(up, down));
            down += mat[1][j];
        }
        cout << answer << "\n";
    }
    return 0;
}