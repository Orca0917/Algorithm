#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int capacity[501][501];
int flow[501][501];

int mf(int source, int sink) {
    memset(flow, 0, sizeof(flow));

    int ret = 0;
    while (true) {
        queue<int> q;
        vector<int> parent(n + 1, -1);
        parent[source] = source;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();

            for (int i = 1; i <= n; ++i) {
                int left = capacity[here][i] - flow[here][i];
                if (left > 0 && parent[i] == -1) {
                    q.push(i);
                    parent[i] = here;
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int p = sink; p != source; p = parent[p])
            amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);

        for (int p = sink; p != source; p = parent[p]) {
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }

        ret += amount;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        capacity[a][b] = capacity[b][a] = c;
    }

    int u, v; cin >> u >> v;
    cout << mf(u, v) << "\n";
    
    return 0;
}