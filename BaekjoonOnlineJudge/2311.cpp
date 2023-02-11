#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Edge {
    int dest, capacity, flow, cost;
    Edge* rev;

    Edge(int dest, int cap, int cost): dest(dest), capacity(cap), flow(0), cost(cost) {}

    int remain() { return capacity - flow; }

    void add_flow(int amount) {
        flow += amount;
        rev -> flow -= amount;
    }
};

vector<Edge*> adj[1002];

void add_edge(int u, int v, int capacity, int cost) {
    Edge* e1 = new Edge(v, capacity, cost);
    Edge* e2 = new Edge(u, 0, -cost);

    e1 -> rev = e2;
    e2 -> rev = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

int MCMF(int source, int sink) {
    int ret = 0;

    while (true) {
        vector<int> parent(1002, -1);
        parent[source] = source;

        vector<Edge*> path(1002, nullptr);

        vector<bool> isin_queue(1002, false);
        isin_queue[source] = true;

        queue<int> q;
        q.push(source);

        vector<int> dist(1002, 1e9);
        dist[source] = 0;

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* e : adj[here]) {
                int there = e -> dest;
                if (e -> remain() > 0 && dist[there] > dist[here] + e -> cost) {
                    dist[there] = dist[here] + e -> cost;
                    parent[there] = here;
                    path[there] = e;
                    if (isin_queue[there]) continue;
                    q.push(there);
                    isin_queue[there] = true;
                }
            }
        }

        if (parent[sink] == -1) break;

        for (int c = sink; c != source; c = parent[c]) {
            path[c] -> add_flow(1);
            ret += path[c] -> cost;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;

    while (m--) {
        int u, v, c; cin >> u >> v >> c;
        add_edge(u, v, 1, c);
        add_edge(v, u, 1, c);
    }

    add_edge(0, 1, 2, 0);
    add_edge(n, n + 1, 2, 0);

    cout << MCMF(0, n + 1) << "\n";
    
    return 0;
}