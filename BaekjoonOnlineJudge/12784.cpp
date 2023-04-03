#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 1001

using namespace std;

int num_island;
int num_bridge;

vector<bool> is_leaf(MAX, false);
vector<pii> adj[MAX];
vector<bool> vis(MAX, false);
int memo[MAX];

void bfs(int node) {
    queue<int> q;
    q.push(node);
    vis[node] = true;

    while (!q.empty()) {
        int here = q.front(); q.pop();

        bool leaf = true;
        for (pii E : adj[here]) {
            if (vis[E.first]) continue;
            leaf = false;
            vis[E.first] = true;    
            q.push(E.first);
        }

        is_leaf[here] = leaf;
    }
}

int dp(int node) {
    // 리프라서 무조건 잘라내야 함
    if (is_leaf[node]) return adj[node].front().second;

    int &ret = memo[node];
    if (ret != -1) return ret;

    ret = 0;
    for (pii E : adj[node]) {
        if (vis[E.first]) continue;
        vis[E.first] = true;
        ret += min(dp(E.first), E.second); // min(다음에 자를 것, 현재 자를 것)
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        cin >> num_island >> num_bridge;

        if (num_bridge == 0) {
            cout << "0\n";
            continue;
        }
        
        for (int i = 0; i < MAX; ++i) adj[i].clear();

        for (int i = 0; i < num_bridge; ++i) {
            int u, v, c; cin >> u >> v >> c;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }

        fill(vis.begin(), vis.end(), false);
        bfs(1);
        fill(vis.begin(), vis.end(), false);

        memset(memo, -1, sizeof(memo));
        cout << dp(1) << "\n";
    }

    return 0;
}