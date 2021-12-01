#include <bits/stdc++.h>
#define ll long long
using namespace std;

int board[1001][1001];
int hasChanges[1001];

int n, m, k; 
int getVal(int idx) {
    if (hasChanges[idx] != -1) return hasChanges[idx];

    int r = 0, c = idx;
    bool flag = false;
    while (r < n) {
        int &info = board[r][c];
        if (info == 1) {
            flag = true;
            ++c;
        } else if (info == 2) {
            ++r;
        } else if (info == 3) {
            flag = true;
            --c;
        }
        info = 2;
    }

    if (flag == false) hasChanges[idx] = c;
    return c;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
        }

    memset(hasChanges, -1, sizeof(hasChanges));

    for (int i = 0; i < k; ++i) {
        int idx; cin >> idx;
        cout << getVal(idx - 1) + 1 << " ";
    }
    cout << "\n";
    return 0;

}