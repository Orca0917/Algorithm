#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll n, m, a, b, c;
vector<pair<int, ll>> adj[100001];

bool dijk(ll limits) {
    ll dist[100001];
    for (int i = 0; i < 100001; ++i) dist[i] = 1e16;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, a});
    dist[a] = 0;
    
    while (!pq.empty()) {
        ll cost = -pq.top().first;
        int node = pq.top().second;
        pq.pop();


        // 도착지에 도달한 경우
        if (node == b && dist[b] <= c) {
            return true;
        }

        // 우선순위 큐에 의한 Dijkstra 로 continue
        if (dist[node] < cost) {
            continue;
        }

        // 인접한 노드 탐색
        for (auto e : adj[node]) {
            int there = e.first;
            ll new_cost = cost + e.second;
            if (e.second <= limits && new_cost < dist[there]) {
                dist[there] = new_cost;
                pq.push({-new_cost, there});
            }
        }
    }

    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> a >> b >> c;
    for (int i = 0; i < m; ++i) {
        ll from, to, cost; cin >> from >> to >> cost;
        adj[from].emplace_back(to, cost);
        adj[to].emplace_back(from, cost);
    }

    ll lo = 1, hi = 1e14, answer = -1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2LL;
        if (dijk(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    
    return 0;
}