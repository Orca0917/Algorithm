#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct E {
    int here;
    int there;
    int cost;
};

int n;
int total_cost = 0;
int idx = 0, new_edge = 0;

set<int> nodes;
vector<pii> total_cost_edge;
vector<int> parent(205);
vector<E> edges;


int find_f(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find_f(parent[x]);
}


void union_f(int x, int y) {
    x = find_f(x);
    y = find_f(y);
    parent[x] = y;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    for (int i = 0; i <= n; ++i) parent[i] = i;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w; cin >> w;
            if (i < j) {
                if (w < 0) {
                    total_cost += -w;
                    union_f(i, j);
                    nodes.insert(i);
                    nodes.insert(j);
                } else {
                    edges.push_back({i, j, w});
                }
            }
        }
    }
    
    sort(edges.begin(), edges.end(), [](const E &a, const E &b) -> bool {
        return a.cost < b.cost;
    });

    while ((int)nodes.size() < n) {
        int u = edges[idx].here, v = edges[idx].there, c = edges[idx++].cost;
        if (find_f(u) != find_f(v)) {
            total_cost += c;
            total_cost_edge.push_back({u, v});
            union_f(u, v);
            ++new_edge;
            nodes.insert(u);
            nodes.insert(v);
        }
    }


    cout << total_cost << " " << new_edge << "\n";
    for (pii &e : total_cost_edge) cout << e.first << " " << e.second << "\n";


    return 0;
}