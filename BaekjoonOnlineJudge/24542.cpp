#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 200001
#define MOD 1'000'000'007

using namespace std;

vector<int> adj[MAX];
vector<int> vis;

ll bfs(int u) {
    ll ret = 1;

    queue<int> q;
    q.push(u);
    vis[u] = true;

    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (int there : adj[here]) {
            if (vis[there]) continue;
            vis[there] = true;
            q.push(there);
            ++ret;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vis.resize(n + 1, false);

    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll answer = 1;
    for (int u = 1; u <= n; ++u) {
        if (!vis[u]) {
            answer *= bfs(u);
            answer %= MOD;
        }
    }

    cout << answer << "\n";

    return 0;
}