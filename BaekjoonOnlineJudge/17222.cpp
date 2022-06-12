#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 202

using namespace std;

int n, m;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];
int limit[MAX];

int network_flow(int source, int sink) {
    int max_flow = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9 * 2;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);

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

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(limit, 0, sizeof(limit));

    cin >> n >> m;

    int source = 0;
    int sink = 201;

    // 주은이의 친구들이 한 명으로부터 전달받을 수 있는 최대 위스키의 양
    for (int i = 1; i <= n; ++i) {
        cin >> limit[i];
        adj[sink].push_back(i);
        adj[i].push_back(sink);
        capacity[i][sink] = 1e9 * 2;
    }

    // 명진이의 친구들이 한 명으로부터 전달받을 수 있는 최대 위스키의 양
    for (int i = n + 1; i <= n + m; ++i) {
        cin >> limit[i];
        adj[source].push_back(i);
        adj[i].push_back(source);
        capacity[source][i] = limit[i];
    }

    // 명진이의 친구들이 연락할 수 있는 연락망
    for (int i = n + 1; i <= n + m; ++i) {
        int k; cin >> k;
        while (k--) {
            int jf; cin >> jf;
            adj[i].push_back(jf);
            adj[jf].push_back(i);
            capacity[i][jf] = limit[jf];
        }
    }

    cout << network_flow(source, sink) << "\n";

    return 0;
}