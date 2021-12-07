/*
 * author: 0917jong
 * date: 2021-12-08
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int n; cin >> n;
    vector<int> a(n);

    for (auto &e : a) cin >> e;

    int answer = 0, targ = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == targ) {
            ++targ;
            ++answer;
            if (targ == 3) targ = 0;
        }
    }

    cout << answer << "\n";
    return 0;
}

