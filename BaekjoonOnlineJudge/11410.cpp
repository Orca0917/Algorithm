#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 52

using namespace std;

struct Edge {
    int destination, capacity, flow = 0, cost;
    Edge* reverse;

    Edge(int destination, int capacity, int cost): destination(destination), capacity(capacity), cost(cost) {}

    int remain() { return capacity - flow; }

    void add_flow(int amount) {
        flow += amount;
        reverse -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];

void add_edge(int u, int v, int capacity, int cost) {
    Edge* e1 = new Edge(v, capacity, cost);
    Edge* e2 = new Edge(u, 0, -cost);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

int MCMF(int source, int sink) {
    int max_ret = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<int> dist(MAX, 1e9);
        dist[source] = 0;

        queue<int> q;
        q.push(source);

        vector<Edge*> path(MAX, nullptr);
        
        while (!q.empty()) {
            int here = q.front(); q.pop();
            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> remain() && dist[there] > dist[here] + edge -> cost) {
                    dist[there] = dist[here] + edge -> cost;
                    parent[there] = here;
                    path[there] = edge;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int e = sink; e != source; e = parent[e])
            amount = min(amount, path[e] -> remain());

        for (int e = sink; e != source; e = parent[e]) {
            path[e] -> add_flow(amount);
            max_ret += amount * path[e] -> cost;
        }
    }

    return max_ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int num_station; cin >> num_station;
    int max_people; cin >> max_people;

    int wants[51][51];
    for (int start = 1; start < num_station; ++start) {
        for (int going = 1; start + going <= num_station; ++going) {
            cin >> wants[start][start + going];
        }
    }

    for (int start = 1; start < num_station; ++start) {
        for (int going = 1; start + going <= num_station; ++going) {
            int cost; cin >> cost;
            add_edge(start, start + going, wants[start][start + going], -cost);
        }
        add_edge(start, start + 1, 1e9, 0);
    }

    int source = 0, sink = num_station + 1;
    add_edge(source, 1, max_people, 0);
    add_edge(num_station, sink, max_people, 0);

    cout << -MCMF(source, sink) << "\n";
    
    return 0;
}