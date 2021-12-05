/*
 * author: 0917jong
 * date: 2021-12-06
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

struct Rank {
    int r[5];
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<Rank> athlete(n);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 5; ++j)
                cin >> athlete[i].r[j];

        int winner = 0;
        for (int i = 0; i < n; ++i) {
            int winCnt = 0;
            for (int j = 0; j < 5; ++j) {
                winCnt += (athlete[i].r[j] < athlete[winner].r[j]);
            }
            if (winCnt >= 3) winner = i;
        }

        for (int i = 0; i < n; ++i) {
            int winCnt = 0;
            for (int j = 0; j < 5; ++j) {
                winCnt += (athlete[i].r[j] < athlete[winner].r[j]);
            }
            if (winCnt >= 3) {
                cout << "-1\n";
                goto A;
            }
        }

        cout << winner + 1 << "\n";

        A:
            continue;
    }
    return 0;
}

