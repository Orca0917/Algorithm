#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1102
#define INF 1e9
using namespace std;

struct Edge {
    int destination, capacity, flow = 0;
    Edge* reverse;

    Edge(int destination, int capacity):
        destination(destination), capacity(capacity) {}

    int remain() {
        return capacity - flow;
    }

    void add_flow(int amount) {
        flow += amount;
        reverse -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];
set<int> keys[MAX];

void add_edge(int u, int v, int capacity) {
    Edge* e1 = new Edge(v, capacity);
    Edge* e2 = new Edge(u, 0);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}


int maximum_flow(int source, int sink) {
    int max_amount = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        vector<bool> isin_queue(MAX, false);
        isin_queue[source] = true;

        vector<Edge*> path(MAX, nullptr);
        
        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> remain() > 0 && parent[there] == -1) {
                    parent[there] = here;
                    path[there] = edge;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = INF;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, path[node] -> remain());

        for (int node = sink; node != source; node = parent[node])
            path[node] -> add_flow(amount);

        max_amount += amount;
    }

    return max_amount;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int num_cage, num_people; cin >> num_cage >> num_people;
    int source = 0, sink = num_cage + num_people + 1;

    for (int cage = 1; cage <= num_cage; ++cage) {
        int capacity; cin >> capacity;
        add_edge(cage, sink, capacity);
    }

    for (int person = num_cage + 1; person <= num_cage + num_people; ++person) {
        int num_key; cin >> num_key;
        for (int idx = 1; idx <= num_key; ++idx) {
            int cage; cin >> cage;
            keys[person].insert(cage);
            add_edge(person, cage, INF);
        }
        int num_pig; cin >> num_pig;
        add_edge(source, person, num_pig);
    }

    for (int person = num_cage + 2; person <= num_cage + num_people; ++person) {
        for (int other = num_cage + 1; other < person; ++other) {
            for (int person_key : keys[person]) {
                if (keys[other].find(person_key) != keys[other].end()) {
                    add_edge(person, other, INF);
                    break;
                }
            }
        }
    }
    
    cout << maximum_flow(source, sink) << "\n";

    return 0;
}