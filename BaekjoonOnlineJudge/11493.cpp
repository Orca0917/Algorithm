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

int n, m;
vector<Edge*> adj[502];
vector<int> vertex;
vector<int> coin;

void add_edge(int u, int v, int cost, int cap) {
    Edge* e1 = new Edge(v, cap, cost);
    Edge* e2 = new Edge(u, 0, -cost);

    e1 -> rev = e2;
    e2 -> rev = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

int MCMF(int source, int sink) {
    int ret = 0;
    while (true) {
        vector<int> parent(n + 2, -1);
        parent[source] = source;

        vector<Edge*> path(n + 2, nullptr);

        vector<bool> isin_queue(n + 2, false);
        isin_queue[source] = true;

        queue<int> q;
        q.push(source);

        vector<int> dist(n + 2, 1e9);
        dist[source] = 0;

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* e : adj[here]) {
                int there = e -> dest;
                if (e -> remain() && dist[there] > dist[here] + e -> cost) {
                    dist[there] = dist[here] + e -> cost;
                    parent[there] = here;
                    path[there] = e;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1;
        for (int c = sink; c != source; c = parent[c]) {
            path[c] -> add_flow(amount);
            ret += amount * path[c] -> cost;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        cin >> n >> m;

        for (int i = 0; i < n + 2; ++i) adj[i].clear();
        vertex.resize(n + 2, 0);
        coin.resize(n + 2, 0);

        int source = 0, sink = n + 1;

        for (int i = 1; i <= m; ++i) {
            int u, v; cin >> u >> v;
            add_edge(u, v, 1, 1e9);
            add_edge(v, u, 1, 1e9);
        }

        for (int i = 1; i <= n; ++i) cin >> vertex[i];
        for (int i = 1; i <= n; ++i) cin >> coin[i];


        for (int i = 1; i <= n; ++i) {
            if (vertex[i] && !coin[i]) add_edge(i, sink, 0, 1);
            if (!vertex[i] && coin[i]) add_edge(source, i, 0, 1);
        }
        
        cout << MCMF(source, sink) << "\n";
    }
    
    return 0;
}