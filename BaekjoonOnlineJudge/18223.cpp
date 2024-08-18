#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int v, e, p;
vector<pii> adj[5001];

int dijkstra(int src, int dest) {
    priority_queue<pii> pq;
    pq.push({0, src});

    vector<int> dist(v + 1, 1e9);
    dist[src] = 0;

    while (!pq.empty()) {
        int cur_dist = -pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist > dist[cur_node]) continue;

        for (pii &edge : adj[cur_node]) {
            int nxt_node = edge.first;
            int weight = edge.second;

            if (dist[nxt_node] > cur_dist + weight) {
                dist[nxt_node] = cur_dist + weight;
                pq.push({-dist[nxt_node], nxt_node});
            }
        }
    }

    return dist[dest];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> v >> e >> p;
    while (e--) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int shortest_path = dijkstra(1, v);
    int include_gunwoo = dijkstra(1, p) + dijkstra(p, v);

    if (shortest_path == include_gunwoo)
        cout << "SAVE HIM";
    else
        cout << "GOOD BYE";
    
    return 0;
}