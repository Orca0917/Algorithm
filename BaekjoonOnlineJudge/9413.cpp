#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 603
using namespace std;

struct Edge {
    int destination, capacity, flow = 0, cost;
    Edge* reverse;

    Edge(int destination, int capacity, int cost):
        destination(destination), capacity(capacity), cost(cost) {}

    int remain() {
        return capacity - flow;
    }

    void add_flow(int amount) {
        flow += amount;
        reverse -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];

void add_edge(int u, int v, int cap, int c) {
    Edge* e1 = new Edge(v, cap, c);
    Edge* e2 = new Edge(u, 0, -c);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}


int max_flow(int source, int sink) {
    int ret = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<Edge*> path(MAX, nullptr);

        vector<int> dist(MAX, 1e9);
        dist[source] = 0;

        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int here = q.front(); q.pop();

            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> remain() > 0 && dist[there] > dist[here] + edge -> cost) {
                    dist[there] = dist[here] + edge -> cost;
                    path[there] = edge;
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, path[node] -> remain());

        for (int node = sink; node != source; node = parent[node]) {
            path[node] -> add_flow(amount);
            ret += (amount * path[node] -> cost);
        }
    }

    return -ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        for (int i = 0; i < MAX; ++i) adj[i].clear();

        int n, m; cin >> n >> m;
        int source = 0, sink = 1, src2 = n * 2 + 2;
        add_edge(source, src2, 2, 0);

        for (int i = 1; i <= n; ++i) {
            add_edge(src2, i * 2, 1, 0);
            add_edge(i * 2, i * 2 + 1, 1, -1);
            add_edge(i * 2 + 1, sink, 1, 0);
        }

        for (int i = 1; i <= m; ++i) {
            int u, v; cin >> u >> v;
            add_edge(u * 2 + 1, v * 2, 1, 0);
        }

        cout << max_flow(source, sink) << "\n";
    }
    
    return 0;
}