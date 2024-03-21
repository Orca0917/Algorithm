#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m, p;
int adj[100001];
bool vis[100001];

int dfs(int x) {
    vis[x] = true;

    int nx = adj[x];
    if (nx == -1) return 0;
    if (vis[nx]) return -1;
    
    int dfs_res = dfs(nx);
    if (dfs_res == -1) return -1;
    else return 1 + dfs_res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(adj, -1, sizeof(adj));
    memset(vis, false, sizeof(vis));    
    
    cin >> n >> m >> p;
    for (int i = 1; i <= n; ++i) {
        int a, b; cin >> a >> b;
        if (adj[b] == -1) adj[b] = a;
    }

    cout << dfs(p) << "\n";

    return 0;
}