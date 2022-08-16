#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
vector<int> adj[100001];

int level[100'001];
bool vis[100'001];

int bfs(int x, vector<int> &order) {
    queue<int> q;
    q.push(1);
    vis[x] = true;

    int index = 1;

    while (!q.empty()) {
        int here = q.front(); q.pop();

        int adj_size = adj[here].size() - 1;
        if (here == 1) adj_size += 1;
        while (adj_size--) {
            int targ = order[index++];
            if (find(adj[here].begin(), adj[here].end(), targ) == adj[here].end()) return 0;
            if (vis[targ]) return 0;
            vis[targ] = true;
            q.push(targ);
        }
    }

    return 1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(level, 1, sizeof(level));
    memset(vis, false, sizeof(vis));


    vector<int> order(n);
    for (int i = 0; i < n; ++i) cin >> order[i];
    for (int i = 1; i <= n; ++i) sort(adj[i].begin(), adj[i].end());

    cout << bfs(1, order) << "\n";

    return 0;
}