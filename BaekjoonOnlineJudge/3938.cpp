#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 367

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


int MCMF(int source, int sink) {
    int ret = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<Edge*> path(MAX, nullptr);

        vector<bool> isin_queue(MAX, false);
        isin_queue[source] = true;

        vector<int> dist(MAX, 1e9);
        dist[source] = 0;

        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> remain() && dist[there] > dist[here] + edge -> cost) {
                    dist[there] = dist[here] + edge -> cost;
                    path[there] = edge;
                    parent[there] = here;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
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
            ret += amount * path[node] -> cost;
        }
    }

    return -ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;

        int source = 0, sink = 366;

        for (int i = 0; i < 366; ++i) adj[i].clear();


        for (int i = 1; i <= n; ++i) {
            int u, v, c; cin >> u >> v >> c;
            add_edge(u - 1, v, 1, -c);
        }

        for (int i = 0; i < 366; ++i) add_edge(i, i + 1, 2, 0);
        cout << MCMF(source, sink) << "\n";
    }
    
    return 0;
}