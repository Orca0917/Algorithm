#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;

vector<pii> adj[1001];

int bfs(int s, int e) {
    vector<bool> vis(1001, false);
    queue<pii> q;
    q.push({s, 0});
    vis[s] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int c = q.front().second;
        q.pop();

        if (x == e)
            return c;

        for (pii t : adj[x]) {
            if (vis[t.first]) continue;
            vis[t.first] = true;
            q.push({t.first, c + t.second});
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i < n; ++i) {
        int s, e, c; cin >> s >> e >> c;
        adj[s].emplace_back(e, c);
        adj[e].emplace_back(s, c);
    }

    while (m--) {
        int s, e; cin >> s >> e;
        cout << bfs(s, e) << "\n";
    }
    return 0;
}