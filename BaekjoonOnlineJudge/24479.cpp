#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m, r;
vector<int> adj[100001];
int vis[100001];
int cnt = 1;

void dfs(int idx) {
    vis[idx] = cnt++;
    for (int x : adj[idx]) {
        if (!vis[x]) dfs(x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> r;
    for (int i = 0; i < m; ++i) {
        int u, v; cin  >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) sort(adj[i].begin(), adj[i].end());

    memset(vis, 0, sizeof(vis));
    dfs(r);

    for (int i = 1; i <= n; ++i) cout << vis[i] << "\n";
    
    return 0;
}