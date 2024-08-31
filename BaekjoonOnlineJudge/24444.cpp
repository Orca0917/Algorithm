#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<int> adj[100001];
int vis[100001];
int cnt = 1;

void bfs(int src) {
    queue<int> q;
    q.push(src);
    vis[src] = cnt++;

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int there : adj[x]) {
            if (vis[there] != 0) continue;
            vis[there] = cnt++;
            q.push(there);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m, r; cin >> n >> m >> r;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i)
        sort(adj[i].begin(), adj[i].end());

    memset(vis, 0, sizeof(vis));
    bfs(r);

    for (int i = 1; i <= n; ++i)
        cout << vis[i] << "\n";

    return 0;
}