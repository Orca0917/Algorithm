#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, r, gig = -1;
vector<pii> adj[200001];
bool vis[200001];

int dfs_gig(int x) {
    vis[x] = true;
    
    if (gig == -1 && ((x == r && adj[x].size() >= 2) || (x != r && adj[x].size() >= 4))) {
        gig = x;
        return 0;
    }

    int ret = 0;
    for (pii nx : adj[x]) {
        if (vis[nx.first]) continue;
        ret = max(ret, dfs_gig(nx.first) + nx.second);
    }

    return ret;
}

int dfs_leaf(int x) {
    vis[x] = true;

    if (adj[x].size() == 1) return 0;

    int ret = 0;
    for (pii nx : adj[x]) {
        if (vis[nx.first]) continue;
        ret = max(ret, dfs_leaf(nx.first) + nx.second);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(vis, false, sizeof(vis));

    cin >> n >> r;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, d; cin >> a >> b >> d;
        adj[a].push_back({b, d});
        adj[b].push_back({a, d});
    }

    int root_giga = dfs_gig(r);
    cout << root_giga << " ";

    // cout << "gig(" << gig << ") ";

    int giga_leaf = dfs_leaf(gig);
    cout << giga_leaf << "\n";
    
    return 0;
}