#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 502
using namespace std;

struct Edge {
    int destination, capacity, flow = 0;
    Edge* reverse = nullptr;

    Edge(int destination, int capacity) : destination(destination), capacity(capacity) {}

    int remain() { return capacity - flow; }

    void add_flow(int amount) {
        flow += amount;
        reverse -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];

void add_edge(int u, int v, int capacity) {
    Edge* e1 = new Edge(v, capacity);
    Edge* e2 = new Edge(u, 0);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

int network_flow(int source, int sink) {
    int ret = 0;
    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<Edge*> path(MAX, nullptr);

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> remain() && parent[there] == -1) {
                    parent[there] = here;
                    path[there] = edge;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        for (int node = sink; node != source; node = parent[node]) {
            path[node] -> add_flow(1);
        }

        ret += 1;
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int num_cow, num_food, num_drink;
    cin >> num_cow >> num_food >> num_drink;
    
    int source = 0, sink = 1;
    for (int drink = 0; drink < num_drink; ++drink)
        add_edge(source, 300 + drink, 1);

    for (int food = 0; food < num_food; ++food)
        add_edge(400 + food, sink, 1);

    for (int cow = 1; cow <= num_cow; ++cow) // 2 ~ 201
        add_edge(cow * 2, cow * 2 + 1, 1);

    for (int cow = 1; cow <= num_cow; ++cow) {
        int want_food, want_drink; cin >> want_food >> want_drink;
        for (int i = 1; i <= want_food; ++i) {
            int food; cin >> food;
            add_edge(cow * 2 + 1, 400 + food - 1, 1);
        }

        for (int i = 1; i <= want_drink; ++i) {
            int drink; cin >> drink;
            add_edge(300 + drink - 1, cow * 2, 1);
        }
    }

    cout << network_flow(source, sink) << "\n";

    return 0;
}