#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;

struct Edge {
    int from, to, cost;
};
vector<Edge> edges;
int parent[200001];

int _find(int x) {
    if (parent[x] != x)
        return parent[x] = _find(parent[x]);
    return x;
}

void _union(int x, int y) {
    x = _find(x);
    y = _find(y);
    parent[x] = y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        edges.clear();
        edges.resize(m);
        for (int i = 0; i <= n; ++i) parent[i] = i;

        for (Edge &edge : edges) cin >> edge.from >> edge.to >> edge.cost;
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) -> bool {
            return a.cost < b.cost;
        });

        ll tot = 0;
        for (Edge e : edges) tot += e.cost;

        int idx = 0;
        ll install = 0;
        int selected = 0;
        while (selected < n - 1 && idx < m) {
            int a = edges[idx].from;
            int b = edges[idx].to;
            int c = edges[idx++].cost;

            if (_find(a) == _find(b)) continue;
            _union(a, b);
            install += c;
            selected += 1;
        }

        cout << tot - install << "\n";
    }
    
    return 0;
}