#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 도시의 수
int P; // 도시를 연결하는 간선의 수
int node1, node2;
int capacity[1000][1000], flow[1000][1000];

vector<int> adj[1000];

int ff(int source, int sink) {
    int max_flow = 0;

    while (true) {
        vector<int> parent(1000, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (int there : adj[here]) {
                if (parent[there] == -1 && capacity[here][there] - flow[here][there] > 0) {
                    q.push(there);
                    parent[there] = here;
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
    
    //// initialize ////
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    //// get input ////
    cin >> N >> P;

    for (int node = 1; node <= N; ++node) {
        adj[node * 2].push_back(node * 2 + 1);
        adj[node * 2 + 1].push_back(node * 2);
        capacity[node * 2][node * 2 + 1] = 1;
    }

    while (P--) {
        cin >> node1 >> node2;
        int node1_in = node1 * 2;
        int node1_out = node1 * 2 + 1;

        int node2_in = node2 * 2;
        int node2_out = node2 * 2 + 1;

        adj[node1_out].push_back(node2_in);
        adj[node2_in].push_back(node1_out);

        adj[node2_out].push_back(node1_in);
        adj[node1_in].push_back(node2_out);
        
        capacity[node1_out][node2_in] = 1;
        capacity[node2_out][node1_in] = 1;
    }

    //// link to source & sink ////
    int source = 2;
    int sink = 5;

    capacity[2][3] = 1e9;
    capacity[4][5] = 1e9;

    cout << ff(source, sink) << "\n";

    return 0;
}