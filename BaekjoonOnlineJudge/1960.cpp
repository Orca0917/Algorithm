#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> adj[1001];
int capacity[1001][1001], flow[1001][1001], answer[1001][1001];

void network_flow(int source, int sink) {
    while (true) {
        vector<int> parent(1001, -1);
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

        int amount = 1e9;
        for (int node = sink; node != source; node = parent[node]) {
            amount= min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(answer, 0, sizeof(answer));

    int n; cin >> n; // 행렬의 크기

    int source = 0, sink = n * 2 + 1;

    // source -> row node
    for (int row_node = 1; row_node <= n; ++row_node) {
        int limit; cin >> limit;

        adj[source].push_back(row_node);
        adj[row_node].push_back(source);

        capacity[source][row_node] = limit;
    }

    // row node -> col node
    for (int row_node = 1; row_node <= n; ++row_node) {
        for (int col_node = 1 + n; col_node <= 2 * n; ++col_node) {
            adj[row_node].push_back(col_node);
            adj[col_node].push_back(row_node);

            capacity[row_node][col_node] = 1;
        }
    }

    // col node -> sink
    for (int col_node = 1 + n; col_node <= n + n; ++col_node) {
        int limit; cin >> limit;

        adj[col_node].push_back(sink);
        adj[sink].push_back(col_node);

        capacity[col_node][sink] = limit;
    }

    network_flow(source, sink);

    // check
    for (int row_node = 1; row_node <= n; ++row_node) {
        for (int col_node = 1 + n; col_node <= n + n; ++col_node) {
            if (flow[row_node][col_node])
                answer[row_node][col_node - n] = 1;
        }
    }

    bool can_make_matrix = true;
    for (int row = 1; row <= n; ++row) {
        int row_sum = 0;
        for (int col = 1; col <= n; ++col) {
            row_sum += answer[row][col];
        }

        if (row_sum != capacity[source][row]) can_make_matrix = false;
    }

    for (int col = 1; col <= n; ++col) {
        int col_sum = 0;
        for (int row = 1; row <= n; ++row) {
            col_sum += answer[row][col];
        }

        if (col_sum != capacity[col + n][sink]) can_make_matrix = false;
    }

    if (!can_make_matrix) cout << "-1\n";
    else {
        cout << "1\n";
        for (int i = 1; i <=n ;++i) {
            for (int j = 1; j <= n; ++j) {
                cout << answer[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}