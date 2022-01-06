#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pil pair<int, ll>

using namespace std;

const ll inf = 1234567890;
int n, m, s, e;
vector<pil> adj[1001];
int backFrom[1001];

vector<int> dijkstra(int src) {
    vector<ll> dist(n + 1, inf);
    dist[src] = 0;
    backFrom[src] = src;

    priority_queue<pair<ll, int>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        ll nowCost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < nowCost) continue;

        for (pil there : adj[here]) {
            if (nowCost + there.second < dist[there.first]) {
                dist[there.first] = nowCost + there.second;
                pq.push({-dist[there.first], there.first});
                backFrom[there.first] = here;
            }
        }
    }

    vector<int> res;
    int x = e;
    while (backFrom[x] != x) {
        res.push_back(x);
        x = backFrom[x];
    } res.push_back(src);

    cout << dist[e] << "\n";
    return vector<int> (res.rbegin(), res.rend());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int from, to;
        ll cost;
        cin >> from >> to >> cost;
        adj[from].push_back({to, cost});
    }

    cin >> s >> e;

    vector<int> ans = dijkstra(s);

    cout << ans.size() << "\n";
    for (int e : ans) cout << e << " ";
    
    return 0;
}