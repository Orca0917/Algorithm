/*
 * author: 0917jong
 * date: 2021-12-09
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int n, m; cin >> n >> m;
    int j; cin >> j;
    int answer = 0;
    int cur = 1;
    while (j--) {
        int p; cin >> p;
        if (cur <= p && p <= cur + m - 1) answer += 0;
        else {
            if (cur > p) {
                answer += abs(p - cur);
                cur += p - cur;
            }
            else {
                answer += p - (cur + m - 1);
                cur += p - (cur + m - 1);
            }
        }
    }

    cout << answer << "\n";
    return 0;
}

