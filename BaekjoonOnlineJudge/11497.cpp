/*
 * author: 0917jong
 * date: 2021-12-09
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &e: a) cin >> e;
        sort(a.rbegin(), a.rend());

        deque<int> dq;
        for (int i = n - 1; i >= 0; --i) {
            if (i % 2) dq.push_front(a[i]);
            else dq.push_back(a[i]);
        }

        int diff = abs(dq.back() - dq.front());
        for (int i = 1; i < n; ++i)
            diff = max(diff, abs(dq[i] - dq[i - 1]));

        cout << diff << "\n";
    }
    return 0;
}

