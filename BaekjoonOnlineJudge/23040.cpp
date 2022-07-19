#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001

using namespace std;

int N;
vector<int> adj[MAX];
int adj_R[MAX];
char color[MAX];

void bfs_adj_r(int node) {
    queue<int> q;
    q.push(node);

    vector<int> adj_red_list;
    adj_red_list.push_back(node);

    bool vis[MAX];
    memset(vis, false, sizeof(vis));
    vis[node] = true;

    int ret = 1;
    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (int there : adj[here]) {
            if (color[there] == 'R' && vis[there] == false) {
                q.push(there);
                vis[there] = true;
                adj_red_list.push_back(there);
                ++ret;
            }
        }
    }

    for (int node : adj_red_list) adj_R[node] = ret;
}


int get_adj_cnt(int node) {
    int ret = 0;

    for (int there : adj[node]) {
        if (color[there] == 'R') ret += adj_R[there];
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N;    

    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; ++i) cin >> color[i];

    memset(adj_R, -1, sizeof(adj_R));
    for (int i = 1; i <= N; ++i) {
        if (color[i] == 'R' && adj_R[i] == -1) {
            bfs_adj_r(i);
        }
    }


    ll answer = 0;
    for (int i = 1; i <= N; ++i) {
        if (color[i] == 'B') {
            int adj_R_nodes = get_adj_cnt(i);
            answer += adj_R_nodes;
        }
    }

    cout << answer << "\n";

    return 0;
}