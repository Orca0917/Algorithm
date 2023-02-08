#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 2002
using namespace std;

struct Edge {
    int destination, cost, capacity, flow = 0;
    Edge* rev;  // 역방향 간선

    // 생성자
    Edge(int destination, int cost, int capacity): 
        destination(destination), cost(cost), capacity(capacity) {}

    // 남은 용량
    int remain() { 
        return capacity - flow; 
    }

    // 유량 추가
    void add_flow(int amount) {
        flow += amount;
        rev -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];
int V, E;

// 간선 추가
void add_edge(int from, int to, int cost, int capacity) {
    Edge* e1 = new Edge(to, cost, capacity);
    Edge* e2 = new Edge(from, -cost, 0);

    e1 -> rev = e2;
    e2 -> rev = e1;

    adj[from].push_back(e1);
    adj[to].push_back(e2);
}


pii MCMF(int source, int sink) {
    int max_flow_cost = 0;
    int max_flow_cnt = 0;

    while (true) {
        vector<bool> isin_queue(MAX, false);
        isin_queue[source] = true;

        vector<int> dist(MAX, 1e9);
        dist[source] = 0;

        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        Edge* path[MAX];

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* e : adj[here]) {
                int there = e -> destination;
                if (e -> remain() && dist[there] > dist[here] + e->cost) {
                    dist[there] = dist[here] + e->cost;
                    parent[there] = here;
                    path[there] = e;

                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int c = sink; c != source; c = parent[c]) {
            amount = min(amount, path[c] -> remain());
        }

        for (int c = sink; c != source; c = parent[c]) {
            path[c] -> add_flow(amount);
            max_flow_cost += amount * path[c] -> cost;
        }

        max_flow_cnt += 1;
    }

    return {max_flow_cnt, max_flow_cost};
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    while (cin >> V >> E) {
        for (int i = 0; i < MAX; ++i) adj[i].clear();

        for (int i = 1; i <= V; ++i) 
            add_edge(i, i + V, 0, (i == 1 || i == V) ? 2 : 1);

        while (E--) {
            int a, b, c; cin >> a >> b >> c;
            add_edge(a + V, b, c, 1);
        }

        int source = 0, sink = 2 * V + 1;
        add_edge(source, 1, 0, 2);
        add_edge(2 * V, sink, 0, 2);

        cout << MCMF(source, sink).second << "\n";
    }
    
    return 0;
}