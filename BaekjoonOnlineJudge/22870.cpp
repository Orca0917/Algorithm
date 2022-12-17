#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define MAX 200001
#define INF 1LL * 5e9

using namespace std;

int n, m, S, E;
ll dist[MAX];
bool vis[MAX];
int from[MAX];
vector<pll> adj[MAX];

ll dijkstra(int start, int end) {
    priority_queue<pll> pq;
    pq.push({0, -start});
    dist[start] = 0;

    while (!pq.empty()) {
        ll cost = -pq.top().first;
        ll here = -pq.top().second;
        pq.pop();

        if (here == end) break;
        if (dist[here] < cost) continue;

        for (pll e : adj[here]) {
            ll there = e.first;
            ll there_cost = e.second;

            if (vis[there]) continue;

            if (dist[there] > dist[here] + there_cost) {
                dist[there] = dist[here] + there_cost;
                pq.push({-dist[there], -there});
            }
        }
    }

    return dist[end];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) dist[i] = INF;
    for (int i = 1; i <= n; ++i) from[i] = i;

    while (m--) {
        int u, v, c; cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    for (int i = 1; i <= n; ++i) sort(adj[i].begin(), adj[i].end());

    cin >> S >> E;

    memset(vis, false, sizeof(vis));
    ll S2E = dijkstra(E, S);

    ll now = S, cur_cost = 0;
    vis[S] = true;
    while (now != E) {
        for (pll e : adj[now]) {
            if (cur_cost + e.second + dist[e.first] == dist[S]) {
                cur_cost += e.second;
                vis[e.first] = true;
                now = e.first;
                break;
            }
        }
    }

    vis[S] = vis[E] = false;

    for (int i = 1; i <= n; ++i) dist[i] = INF;
    ll E2S = dijkstra(S, E);

    cout << S2E + E2S << "\n";
    
    return 0;
}