#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct EDGE {
    int u, v, w;
};

int n, m, s, e;
vector<EDGE> edges;
vector<int> parent;
vector<pii> adj[100'001];


int find_f(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find_f(parent[x]);
}


void union_f(int x, int y) {
    x = find_f(x);
    y = find_f(y);
    if (x == y) return;
    parent[x] = y;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> s >> e;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    
    sort(edges.begin(), edges.end(), [](const EDGE &a, const EDGE &b) -> bool {
        return a.w > b.w;
    });

    parent.resize(100'001);
    for (int i = 1; i <= n; ++i) parent[i] = i;

    int connection = 0, idx = 0;
    while (connection < n - 1 && idx < edges.size()) {
        int u = edges[idx].u;
        int v = edges[idx].v;
        int w = edges[idx++].w;

        if (find_f(u) != find_f(v)) {
            union_f(u, v);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            ++connection;
            // cout << "connect " << u << " , " << v << "\n";
        }
    }

    priority_queue<pii> pq;
    pq.push({1e9, s});

    vector<bool> vis(100'001, false);
    vis[s] = true;
    int answer = 0;

    while (!pq.empty()) {
        int weight = pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (here == e) {
            answer = weight;
            break;
        }

        for (pii there : adj[here]) {
            if (vis[there.first]) continue;
            vis[there.first] = true;
            pq.push({min(weight, there.second), there.first});
        }
    }

    cout << answer << "\n";

    return 0;
}