#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<ll> V(n);
    for (ll &e : V) cin >> e;
    sort(V.begin(), V.end());

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int start = 0; start < n; ++start) {
            if (start == i) continue;

            ll now = V[start];
            ll trgt = V[i] - now;
            auto it = lower_bound(V.begin(), V.end(), trgt);
            if (it == V.end()) continue;

            while (*it == trgt) {
                int idx = it - V.begin();
                if (idx == start || idx == i) ++it;
                else {
                    ++answer;
                    goto A;
                }
            }
        }

        A:
            continue;
    }

    cout << answer << "\n";
    return 0;
}