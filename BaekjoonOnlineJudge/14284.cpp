#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
vector<pii> adj[5001];
vector<int> dist(5001, 1e9);

int dijkstra(int src, int dst) {
    priority_queue<pii> pq;
    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[cur] < cost) continue;

        for (pii there : adj[cur]) {
            int nxt = there.first;
            int w = there.second;

            if (dist[nxt] > dist[cur] + w) {
                dist[nxt] = dist[cur] + w;
                pq.push({-dist[nxt], nxt});
            }
        }
    }

    return dist[dst];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src, dst; cin >> src >> dst;
    cout << dijkstra(src, dst);
    
    
    return 0;
}