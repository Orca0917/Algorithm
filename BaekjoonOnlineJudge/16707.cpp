#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1005
using namespace std;

struct Edge {
    int to, cost, capacity, flow, rev;
    Edge (int to, int cost, int c, int f, int rev): to(to), cost(cost), capacity(c), flow(f), rev(rev) {}
};

int n, m;
vector<Edge> adj[MAX];

void addEdge(int here, int there, int cost, int capacity) {
    // to, cost, capacity, flow, reverse_index
    adj[here].emplace_back(there, cost, capacity, 0, adj[there].size());
    adj[there].emplace_back(here, cost, capacity, 0, adj[here].size() - 1);
}

int MCMF(int source, int sink) {
    int max_cost = 0;

    while (true) {
        vector<int> parent(MAX, -1), e_parent(MAX, -1);
        vector<int> dist(MAX, 1e9);
        vector<bool> isin_queue(MAX, false);
        queue<int> q;

        parent[source] = source;
        dist[source] = 0;
        isin_queue[source] = true;
        q.push(source);

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            int index =  0;
            for (auto there_info : adj[here]) {
                int there = there_info.to;
                int cost = there_info.cost;
                int flow = there_info.flow;
                int capacity = there_info.capacity;

                if (capacity - flow > 0 && dist[there] > dist[here] + cost) {
                    dist[there] = dist[here] + cost;
                    parent[there] = here;
                    e_parent[there] = index;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push({there});
                }

                ++index;
            }
        }

        if (parent[sink] == -1) break;

        for (int node = sink; node != source; node = parent[node]) {
            int prev = parent[node];
            int idx = e_parent[node];

            cout << prev << " - " << adj[prev][idx].to << " : " << adj[prev][idx].cost << "\n";
            
            max_cost += adj[prev][idx].cost;
            adj[prev][idx].flow += 1;
            adj[node][adj[prev][idx].rev].flow += 1;
        }
    }

    return max_cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    int source = 0, sink = n + 1;
    
    while (m--) {
        int n1, n2, c; cin >> n1 >> n2 >> c;
        addEdge(n1, n2, c, 1);
    }

    addEdge(source, 1, 0, 1);
    addEdge(n, sink, 0, 1);

    int res1 = MCMF(2, source);
    cout << "--" << "\n";
    int res2 = MCMF(2, sink);
    cout << res1 + res2 << "\n";

    return 0;
}