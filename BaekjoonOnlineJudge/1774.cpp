#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 1001

using namespace std;

struct Edge {
    int u;
    int v;
    double dist;
};

vector<int> parent(MAX);
vector<pii> position(MAX);
vector<Edge> edges;

double get_distance(pii a, pii b) {
    ll dist1 = abs(a.first - b.first);
    ll dist2 = abs(a.second - b.second);

    ll pow_dist = dist1 * dist1 + dist2 * dist2;
    return (double)sqrt(pow_dist); 
}

int find_f(int u) {
    if (parent[u] != u) return parent[u] = find_f(parent[u]);
    else return u;
}

void union_f(int u, int v) {
    u = find_f(u);
    v = find_f(v);

    if (u == v) return;

    parent[u] = v;    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // initialize parent node
    for (int i = 0; i < MAX; ++i) parent[i] = i;

    // get god's position
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> position[i].first >> position[i].second;
    }

    // already connected edges
    int connected = 0;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        if (find_f(u) == find_f(v)) continue;
        ++connected;
        union_f(u, v);
    }

    // calculate all distances
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            double dist = get_distance(position[i], position[j]);
            edges.push_back({i, j, dist});
        }
    }

    // sort by distance
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) -> bool {
        return a.dist < b.dist;
    });

    // MST
    double answer = 0;
    for (Edge e : edges) {
        if (connected >= n - 1) break;

        if (find_f(e.u) == find_f(e.v)) continue;

        answer += e.dist;
        union_f(e.u, e.v);
    }

    cout << setprecision(2);
    cout << fixed << answer << "\n";
    
    return 0;
}