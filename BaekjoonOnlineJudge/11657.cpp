#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;


struct Edge {
    int start;
    int end;
    ll cost;
};

vector<Edge> edges;
ll cost[501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cost[i] = 1e10;
    
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }

    // 한 iteration 더 돌았는데 업데이트 되는 것이 존재하면 음사이클 존재   
    bool neg_cycle = false;
    cost[1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (Edge e : edges) {
            if (cost[e.start] == 1e10) continue;
            if (cost[e.end] > cost[e.start] + e.cost) {
                cost[e.end] = cost[e.start] + e.cost;
                if (i == n) neg_cycle = true;
            }
        }  
    }

    if (neg_cycle) cout << "-1\n";
    else {
        for (int i = 2; i <= n; ++i) {
            if (cost[i] == 1e10) cout << -1 << "\n";
            else cout << cost[i] << "\n";
        }
    }

    return 0;
}