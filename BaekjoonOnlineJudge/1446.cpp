#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, d;
vector<pii> adj[10001];
vector<int> dist(10001, -1);

void dijkstra(int start) {
    priority_queue<pii> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost) continue;
        
        if (here == d) break;

        // 그냥 가는 경우
        if (dist[here + 1] == -1 || dist[here + 1] > cost + 1) {
            dist[here + 1] = cost + 1;
            pq.push({-(cost + 1), here + 1});
        }

        // 지름길 사용
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int time_ = adj[here][i].second;

            if (dist[there] != -1 && dist[there] <= cost + time_) continue;

            dist[there] = cost + time_;
            pq.push({-(cost + time_), there});    
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> d;

    while (n--) {
        int u, v, cost; cin >> u >> v;
        adj[u].push_back({v, cost});
    }

    dijkstra(0);
    
    cout << dist[d] << "\n";

    return 0;
}