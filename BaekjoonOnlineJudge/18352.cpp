#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m, k, x;
vector<int> adj[300001];
vector<int> dist(300001, -1);

void dijkstra(int start) {
    priority_queue<pii> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost) continue;

        for (int there : adj[here]) {
            if (dist[there] != -1 && dist[there] <= cost + 1) continue;

            dist[there] = cost + 1;
            pq.push({-(cost + 1), there});
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> k >> x;

    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    dijkstra(x);

    vector<int> answer;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == k) answer.push_back(i);
    }

    if (answer.empty()) cout << "-1\n";
    else for (int e : answer) cout << e << "\n";
    
    return 0;
}