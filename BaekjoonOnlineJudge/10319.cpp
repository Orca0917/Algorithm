#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1002001

using namespace std;

struct Edge {
    int destination, capacity, flow = 0;
    Edge* reverse;

    Edge(int destination, int capacity, int cost): destination(destination), capacity(capacity) {}

    int remain() { return capacity - flow; }

    void add_flow(int amount) {
        flow += amount;
        reverse -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];
int source, num_people, time_zombie;

void add_edge(int u, int v, int capacity) {
    Edge* e1 = new Edge(v, capacity, 1);
    Edge* e2 = new Edge(u, 0, -1);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

int network_flow(int source, int sink) {
    int max_flow = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<Edge*> path(MAX, nullptr);

        queue<pii> q;
        q.push({source, 0});

        int min_time = 0;

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front().first;
            int cost = q.front().second;
            q.pop();

            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> remain() && parent[there] == -1) {
                    parent[there] = here;
                    path[there] = edge;
                    q.push({there, cost + 1});
                }
                if (parent[sink] != -1) min_time = cost;
            }
        }

        if (parent[sink] == -1 || min_time > time_zombie) break;

        int amount = 1e9;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, path[node] -> remain());

        for (int node = sink; node != source; node = parent[node])
            path[node] -> add_flow(amount);

        max_flow += (time_zombie - min_time + 1) * amount;
    }

    return min(num_people, max_flow);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        for (int i = 0; i < MAX; ++i) adj[i].clear();

        int num_node; cin >> num_node;
        int sink = num_node * num_node + num_node;

        cin >> source >> num_people >> time_zombie;

        int num_hospital; cin >> num_hospital;
        while (num_hospital--) {
            int hospital; cin >> hospital;
            add_edge(hospital, sink, 1e9);
        }

        int num_road; cin >> num_road;
        for (int i = 1; i <= num_road; ++i) {
            int u, v, capacity, cost;
            cin >> u >> v >> capacity >> cost;
            
            // source = source
            // node = 1 ~ num_node
            if (cost >= 2) {
                int here = num_node * i + 1;
                for (int j = -1; j < cost - 1; ++j)
                    add_edge((j == -1 ? u : here + j), (j == cost - 2 ? v : here + j + 1), capacity);
            } else
                add_edge(u, v, capacity);
        }

        cout << network_flow(source, sink) << "\n";
    }
    
    return 0;
}