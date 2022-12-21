#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

deque<pii> dq;
vector<int> v[5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll k; cin >> k;

    for (int i = 0; i < 6; ++i) {
        int dir, len; cin >> dir >> len;
        dq.push_back({dir, len});
        v[dir].push_back(len);
    }

    ll small = 0;
    for (int i = 0; i < 6; ++i) {
        if (dq[0].first == dq[2].first && dq[1].first == dq[3].first) {
            small = dq[1].second * dq[2].second;
            break;
        }
        dq.push_back(dq.front());
        dq.pop_front();
    }

    ll big = 1;
    for (int i = 1; i <= 4; ++i) {
        if (v[i].size() == 1) big *= v[i][0];
    }

    cout << k * (big - small) << "\n";

    return 0;
}