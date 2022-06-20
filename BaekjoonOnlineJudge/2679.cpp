#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1001
#define INF 1e9

using namespace std;

int n, e, a, b;
/**
 * @brief 
 * n : number of vertices
 * e : number of edges
 * a : start vertex (source)
 * b : end vertex (sink)
 */

vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];

int bfs_dijkstra(int source, int sink) {
    queue<pii> q;
    q.push({source, INF});

    vector<int> vis(MAX, 0);
    vis[source] = true;

    while (!q.empty()) {
        int here = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int there : adj[here]) {
            int there_max = capacity[here][there];
            int there_flow = min(there_max, flow);
            
            if (vis[there] < there_flow) {
                vis[there] = there_flow;
                q.push({there, there_flow});
            }
        }
    }

    return vis[sink];
}

int network_flow(int source, int sink) {

    memset(flow, 0, sizeof(flow));

    int max_flow = 0;
    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = INF;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }

        max_flow += amount;
    }

    return max_flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        // init
        memset(capacity, 0, sizeof(capacity));

        cin >> n >> e >> a >> b;

        while (e--) {
            int node1, node2, c;
            cin >> node1 >> node2 >> c;

            adj[node1].push_back(node2);
            adj[node2].push_back(node1);
            capacity[node1][node2] = c;
        }

        int max_flow = network_flow(a, b);
        int max_dist = bfs_dijkstra(a, b);

        cout << fixed;
        cout.precision(3);
        cout << max_flow / (double)max_dist << "\n";
    }
    
    return 0;
}