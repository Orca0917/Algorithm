#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    deque<pii> dq;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        dq.push_back({i + 1, x});
    }

    while (dq.size() > 1) {
        pii x = dq.front(); dq.pop_front();
        cout << x.first << " ";

        if (x.second > 0) {
            int mv = x.second - 1;
            while (mv-- > 0) {
                pii y = dq.front(); dq.pop_front();
                dq.push_back(y);
            }
        } else {
            int mv = abs(x.second);
            while (mv-- > 0) {
                pii y = dq.back(); dq.pop_back();
                dq.push_front(y);
            }
        }
    }

    cout << dq.front().first << "\n";
    return 0;
}