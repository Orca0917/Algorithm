#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 2502
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

vector<Edge*> adj[MAX];
char board[51][51];
int movement[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int costs[6][6] = {
    {10, 8, 7, 5, 0, 1},
    {8, 6, 4, 3, 0, 1},
    {7, 4, 3, 2, 0, 1},
    {5, 3, 2, 2, 0, 1},
    {0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0}
};

void add_edge(int u, int v, int cost) {
    Edge* e1 = new Edge(v, 1, cost);
    Edge* e2 = new Edge(u, 0, -cost);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
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
    
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> board[i][j];
        }
    }

    int source = 0, sink = n * m + 1;    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int here = (i - 1) * m + j;
            if (i % 2 == j % 2) {
                add_edge(source, here, 0);
                for (int k = 0; k < 4; ++k) {
                    int x = i + movement[k][0];
                    int y = j + movement[k][1];
                    if (x < 1 || x > n || y < 1 || y > m) continue;
                    int cost = costs[board[x][y] - 'A'][board[i][j] - 'A'];
                    int there = (x - 1) * m + y;
                    add_edge(here, there, -cost); 
                }
            }
            add_edge(here, sink, 0);
        }
    }

    cout << -MCMF(source, sink).second << "\n";

    return 0;
}

