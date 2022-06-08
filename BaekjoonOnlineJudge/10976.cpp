#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX_VERTEX 202
using namespace std;

int V; // 정점의 수
int E; // 간선의 수

vector<int> adj[MAX_VERTEX];
int capacity[MAX_VERTEX][MAX_VERTEX], flow[MAX_VERTEX][MAX_VERTEX];

void init_global_vars() {
    for (int i = 0; i < MAX_VERTEX; ++i)
        adj[i].clear();

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
}

int network_flow(int source, int sink) {
    int max_flow = 0;

    while (true) {
        vector<int> parent(MAX_VERTEX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (int there : adj[here]) {
                if (parent[there] == -1 && capacity[here][there] - flow[here][there] > 0) {
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int node = sink; node != source; node = parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }

        max_flow += amount;
    }

    return max_flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        init_global_vars();

        cin >> V >> E;

        int source = 1, sink = V;
        while (E--) {
            int point1, point2; cin >> point1 >> point2;

            adj[point1].push_back(point2);
            adj[point2].push_back(point1);

            if (point1 == source || point2 == sink) capacity[point1][point2] = 1;
            else capacity[point1][point2] = 1e9;
        }

        cout << network_flow(source, sink) << "\n";
    }
    
    return 0;
}