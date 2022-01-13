#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k, m; cin >> n >> k >> m;

    deque<int> dq;
    for (int i = 1; i <= n; ++i) dq.push_back(i);

    int delCnt = 1;
    for (int i = 0; i < k - 1; ++i) {
        int x = dq.front(); dq.pop_front();
        dq.push_back(x);
    }

    cout << dq.front() << "\n";
    dq.pop_front();

    bool rev = false;
    
    while (!dq.empty()) {
        if (delCnt == m) {
            rev = !rev;
            delCnt = 0;
        }
        
        if (rev) {
            for (int i = 0; i < k; ++i) {
                int x = dq.back(); dq.pop_back();
                dq.push_front(x);
            }
            cout << dq.front() << "\n";
            dq.pop_front();
            ++delCnt;
        } else {
            for (int i = 0; i < k - 1; ++i) {
                int x = dq.front(); dq.pop_front();
                dq.push_back(x);
            }
            cout << dq.front() << "\n";
            dq.pop_front();
            ++delCnt;
        }

        
    }
    return 0;
}