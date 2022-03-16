#include <bits/stdc++.h>
#define ll long long
#define pii pair<long long, long long>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // get input
    int n, k; cin >> n >> k;
    deque<pii> stages(n);
    for (pii &e : stages) cin >> e.first >> e.second;

    // insert start position, end position
    stages.push_front({0, 0});
    stages.push_back({10000, 10000});

    // get squared distance between stationA and stationB
    auto get_dist = [](const pii &a, const pii &b) -> ll {
        ll fi = (a.first - b.first);
        ll se = (a.second - b.second);
        return fi * fi + se * se;
    };
    
    // BFS: is available to go (10000, 10000) from (0, 0)
    auto can_fly = [&](const ll mid) -> bool {

        const int inf = 1e9;
        vector<int> vis(1005, inf);    
        queue<pii> q;

        q.push({0, 0});
        vis[0] = 0;

        while (!q.empty()) {
            int index = q.front().first;
            int count = q.front().second;
            q.pop();

            // arrived destination within k counts
            if (index == n + 1 && count <= k + 1) return true;

            // check all stations
            for (int i = 1; i <= n + 1; ++i) {
                if (vis[i] <= count + 1) continue;

                // is available to go there with "mid" oil?
                if (get_dist(stages[index], stages[i]) <= 100 * mid * mid) {
                    q.push({i, count + 1});
                    vis[i] = count + 1;
                }
            }
        }
        
        return false;
    };

    ll lo = 1, hi = get_dist({0, 0}, stages.back()), answer = 1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2LL;
        if (can_fly(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";

    return 0;
}