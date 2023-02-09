#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
int cap[502][502], flow[502][502];
int work[502], level[502];
vector<int> adj[502]; 

void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void add_flow(int u, int v, int amount) {
    flow[u][v] += amount;
    flow[v][u] -= amount;
}

int remain(int u, int v) {
    return cap[u][v] - flow[u][v];
}

bool bfs(int source, int sink) {
    memset(level, -1, sizeof(level));
    level[source] = 0;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (int there : adj[here]) {
            if (level[there] == -1 && remain(here, there) > 0) {
                level[there] = level[here] + 1;
                q.push(there);
            }
        }
    }

    return level[sink] != -1;
}

int dfs(int cur, int dest, int flow) {
    if (cur == dest) return flow;

    for (int &i = work[cur]; i < adj[cur].size(); ++i) {
        int there = adj[cur][i];
        if (level[there] == level[cur] + 1 && remain(cur, there) > 0) {
            int res = dfs(there, dest, min(remain(cur, there), flow));
            if (res > 0) {
                add_flow(cur, there, res);
                return res;
            }
        }
    }

    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(cap, 0, sizeof(cap));
    memset(flow, 0, sizeof(flow));

    cin >> n;
    int source = 0, sink = 501;
    for (int i = 1; i <= n; ++i) {
        int k; cin >> k;
        if (k == 1) {
            cap[source][i] = 1e9;
            add_edge(source, i);
        }
        else if (k == 2) {
            cap[i][sink] = 1e9;
            add_edge(i, sink);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> cap[i][j];
            if (i != j) adj[i].push_back(j);
        }
    }

    int total = 0;
    while (bfs(source, sink)) {
        memset(work, 0, sizeof(work));
        while (true) {
            int flow = dfs(source, sink, 1e9);
            if (flow == 0) break;
            total += flow;
        }
    }
    cout << total << "\n";

    vector<bool> vis(502, false);
    vis[source] = true;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (int there : adj[here]) {
            if (!vis[there] && remain(here, there) > 0) {
                vis[there] = true;
                q.push(there);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (vis[i]) cout << i << " ";
    } cout << "\n";

    for (int i = 1; i <= n; ++i)
        if (!vis[i]) cout << i << " ";
    cout << "\n";
    
    return 0;
}