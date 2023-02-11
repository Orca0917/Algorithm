#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 402
#define INF 1e9

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

struct Line {
    int x1, y1, x2, y2, weight;
};

vector<Edge*> adj[MAX];

void add_edge(int u, int v, int cost) {
    Edge* e1 = new Edge(v, 1, cost);
    Edge* e2 = new Edge(u, 0, -cost);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

bool is_intersect(Line a, Line b) {
    if (a.x1 > a.x2) swap(a.x1, a.x2);
    if (b.y1 > b.y2) swap(b.y1, b.y2);

    return (b.y1 < a.y1 && a.y1 < b.y2 && a.x1 < b.x1 && b.x1 < a.x2);
}

pii MCMF(int source, int sink) {
    int max_flow = 0;
    int max_cost = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<int> dist(MAX, INF);
        dist[source] = 0;

        vector<Edge*> path(MAX, nullptr);

        queue<int> q;
        q.push(source);

        vector<bool> isin_queue(MAX, false);
        isin_queue[source] = true;

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

        int amount = 1;
        for (int node = sink; node != source; node = parent[node]) {
            path[node] -> add_flow(amount);
            max_cost += amount * path[node] -> cost;
        }

        max_flow += amount;
    }

    return {max_flow, max_cost};
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        for (int i = 0; i < MAX; ++i) adj[i].clear();

        int num_horizontal, num_vertical; cin >> num_horizontal >> num_vertical;
        int source = 0, sink = num_horizontal + num_vertical + 1;

        vector<Line> h_lines(num_horizontal + 1), v_lines(num_vertical + 1);
        for (int horizontal = 1; horizontal <= num_horizontal; ++horizontal) {
            Line &line = h_lines[horizontal];
            cin >> line.x1 >> line.y1 >> line.x2 >> line.y2 >> line.weight;
            add_edge(source, horizontal, 0);
        }

        for (int vertical = 1; vertical <= num_vertical; ++vertical) {
            Line &line = v_lines[vertical];
            cin >> line.x1 >> line.y1 >> line.x2 >> line.y2 >> line.weight;
            add_edge(num_horizontal + vertical, sink, 0);
        }

        for (int horizontal = 1; horizontal <= num_horizontal; ++horizontal) {
            for (int vertical = 1; vertical <= num_vertical; ++vertical) {
                if (is_intersect(h_lines[horizontal], v_lines[vertical])) {
                    int cost = h_lines[horizontal].weight * v_lines[vertical].weight;
                    add_edge(horizontal, num_horizontal + vertical, -cost);
                }
            }
        }

        pii result = MCMF(source, sink);
        // pii result = {1, 2};
        cout << result.first << " " << -result.second << "\n";
    }
    
    return 0;
}