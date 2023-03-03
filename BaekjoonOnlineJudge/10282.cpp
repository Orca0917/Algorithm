#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 10001

using namespace std;

vector<pii> adj[MAX];

pii dijkstra(int source) {
    vector<int> dist(MAX, 1e9);
    dist[source] = 0;

    priority_queue<pii> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        // if (dist[here] < cost) continue;

        for (pii e : adj[here]) {
            if (dist[e.first] > dist[here] + e.second) {
                dist[e.first] = dist[here] + e.second;
                pq.push({-(dist[here] + e.second), e.first});
            }
        }
    }

    int hacked = 0;
    int time_all = 0;
    for (int i = 0; i < MAX; ++i) {
        if (dist[i] != 1e9) {
            hacked += 1;
            time_all = max(dist[i], time_all);
        }
    }

    return {hacked, time_all};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        for (int i = 0; i < MAX; ++i) adj[i].clear();

        int num_computer; cin >> num_computer;
        int num_edge; cin >> num_edge;
        int num_hacked; cin >> num_hacked;

        while (num_edge--) {
            int u, v, c; cin >> u >> v >> c;
            adj[v].push_back({u, c});
        }

        pii ret = dijkstra(num_hacked);
        cout << ret.first << " " << ret.second << "\n";
    }
    
    return 0;
}