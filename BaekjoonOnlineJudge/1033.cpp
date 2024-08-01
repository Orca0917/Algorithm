#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Node {
    int node;
    ll p, q;
};

vector<Node> edges[11];
pair<ll, ll> dist[11];
bool vis[11];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    // a -> b    =>    b = a * (p / q);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, p, q; cin >> a >> b >> p >> q;
        edges[a].push_back({b, p, q});
        edges[b].push_back({a, q, p});
    }

    dist[0] = make_pair(1, 1);
    
    memset(vis, false, sizeof(vis));

    queue<Node> que;
    que.push({0, 1, 1});
    vis[0] = true;

    while (!que.empty()) {
        int node = que.front().node;
        int p = que.front().p;
        int q = que.front().q;
        que.pop();

        for (Node n : edges[node]) {
            if (vis[n.node]) continue;
            vis[n.node] = true;

            ll val1 = p * n.p;
            ll val2 = q * n.q;
            ll gcd = __gcd(val1, val2);
            dist[n.node] = make_pair(val1 / gcd, val2 / gcd);
            que.push({n.node, dist[n.node].first, dist[n.node].second});
        }
    }

    ll lcs = 1;
    for (int i = 1; i < n; ++i)
        lcs = lcs * dist[i].first / __gcd(lcs, dist[i].first);

    for (int i = 0; i < n; ++i)
        cout << dist[i].second * (lcs / dist[i].first) << " ";


    return 0;
}