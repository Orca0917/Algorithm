#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, S, E;

struct Edge {
    ll dest, capacity, flow = 0;
    Edge* rev;

    Edge(int dest, ll cap):
        dest(dest), capacity(cap) {}

    ll remain() {
        return capacity - flow;
    }

    void add_flow(ll amount) {
        flow += amount;
        rev -> flow -= amount;
    }
};

vector<Edge*> adj[404];

void add_edge(int u, int v, ll cap) {
    Edge* e1 = new Edge(v, cap);
    Edge* e2 = new Edge(u, 0);

    e1 -> rev = e2;
    e2 -> rev = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

void MCMF(int source, int sink) {
    while (true) {
        vector<int> parent(n * 2 + 3, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        vector<bool> isin_queue(n * 2 + 3, false);
        isin_queue[source] = true;

        vector<Edge*> path(n * 2 + 3, nullptr);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* e : adj[here]) {
                int there = e -> dest;
                if (e -> remain() && parent[there] == -1) {
                    parent[there] = here;
                    path[there] = e;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        ll amount = 1e11;
        for (int c = sink; c != source; c = parent[c])
            amount = min(amount, path[c] -> remain());

        for (int c = sink; c != source; c = parent[c])
            path[c] -> add_flow(amount);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> S >> E;

    // 정점 분할
    for (int i = 1; i <= n; ++i) {
        int cost; cin >> cost;
        add_edge(i * 2, i * 2 + 1, cost);
    }
    
    // 톨게이트 간 연결 -> 고속도로 건설 (양방향?)
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        add_edge(u * 2 + 1, v * 2, 1e11);
        add_edge(v * 2 + 1, u * 2, 1e11);
    }

    int source = S * 2, sink = E * 2 + 1;

    MCMF(source, sink);

    vector<bool> vis(2 * n + 3, false);
    vis[source] = true;
    
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (Edge* e : adj[here]) {
            int there = e -> dest;
            if (vis[there] == false && e -> remain()) {
                vis[there] = true;
                q.push(there);
            }
        }
    }

    for (int i = 1; i <= n; ++i)
        if (vis[i * 2] && !vis[i * 2 + 1])
            cout << i << " ";
    
    return 0;
}