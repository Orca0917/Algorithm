#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 2502
using namespace std;

struct Edge {
    int destination, capacity, flow = 0;
    Edge* reverse;

    Edge(int destination, int capacity): destination(destination), capacity(capacity) {}

    int remain() {
        return capacity - flow;
    }

    void add_flow(int amount) {
        flow += amount;
        reverse -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];
int movement[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

void add_edge(int u, int v, int cap) {
    Edge* e1 = new Edge(v, cap);
    Edge* e2 = new Edge(u, 0);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

int max_flow(int source, int sink) {
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

        int amount = 1e9;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, path[node] -> remain());

        for (int node = sink; node != source; node = parent[node])
            path[node] -> add_flow(amount);

        ret += amount;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        for (int i = 0; i < MAX; ++i) adj[i].clear();

        int n, m; cin >> n >> m;
        int source = 0, sink = n * m + 1;
        int tot = 0;

        int board[51][51];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> board[i][j];
                tot += board[i][j];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int here = (i - 1) * m + j;
                if ((i & 1) == (j & 1)) {
                    add_edge(source, here, board[i][j]);
                    for (int k = 0; k < 4; ++k) {
                        int x = i + movement[k][0];
                        int y = j + movement[k][1];
                        if (x < 1 || x > n || y < 1 || y > m) continue;
                        int there = (x - 1) * m + y;
                        add_edge(here, there, 1e9);
                    }
                } else {
                    add_edge(here, sink, board[i][j]);
                }
            }
        }

        cout << tot - max_flow(source, sink) << "\n";
    }
    
    return 0;
}