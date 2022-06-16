#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 102

using namespace std;

int n; // size of matrix
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];
int lim[MAX], row_sum = 0, col_sum = 0;

void init_capacity(int val) {
    for (int row = 1; row <= n; ++row)
        for (int col = 51; col <= 50 + n; ++col)
            capacity[row][col] = val;
}

bool network_flow(int source, int sink) {
    int max_flow = 0;

    // init flows
    memset(flow, 0, sizeof(flow));

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

    return row_sum == col_sum && row_sum == max_flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    // init values
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    int source = 0, sink = 101;
    
    // get row sum info.
    for (int row = 1; row <= n; ++row) {
        cin >> lim[row];
        row_sum += lim[row];
    }

    // get col sum info.
    for (int col = 51; col <= 50 + n; ++col) {
        cin >> lim[col];
        col_sum += lim[col]; 
    }

    // connect sink & source to nodes
    for (int row = 1, col = 51; row <= n; ++row, ++col) {
        adj[source].push_back(row);
        adj[col].push_back(sink);

        capacity[source][row] = lim[row];
        capacity[col][sink] = lim[col];
    }

    // connect rows & cols
    for (int row = 1; row <= n; ++row) {
        for (int col = 51; col <= 50 + n; ++col) {
            adj[row].push_back(col);
            adj[col].push_back(row);
            // capactiy in binary search
        }
    }

    // binary search
    int lo = 0, hi = 1e5, answer = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        init_capacity(mid);

        if (network_flow(source, sink)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    init_capacity(answer);
    network_flow(source, sink);

    // printing answer
    cout << answer << "\n";
    for (int row = 1; row <= n; ++row) {
        for (int col = 51; col <= 50 + n; ++col) {
            cout << flow[row][col] << " ";
        }
        cout << "\n";
    }
        
    return 0;
}