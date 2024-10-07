#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n; // 발전소의 수
int w; // 남아있는 전선의 수
double m; // 제한 길이

vector<pii> power_station;
vector<pair<int, double>> adj[1000];

double _distance(int i, int j) {
    ll dx = power_station[i].first - power_station[j].first;
    ll dy = power_station[i].second - power_station[j].second;
    return sqrt((long double)(dx * dx + dy * dy));
}

int dijkstra(int src, int dst) {
    priority_queue<pair<double, int>> pq;
    pq.push({0, src});
    
    vector<double> dist(n, 1e9);
    dist[src] = 0;

    while (!pq.empty()) {
        double cur_dist = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] > cur_dist) continue;

        for (auto nxt : adj[here]) {
            int there = nxt.first;
            double cost = nxt.second;

            if (dist[there] > dist[here] + cost) {
                dist[there] = dist[here] + cost;
                pq.push({-dist[there], there});
            }
        }
    }

    return floor(dist[dst] * 1000);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> w >> m;

    power_station.resize(n);
    for (pii &e : power_station) cin >> e.first >> e.second;
    
    // 가능한 모든 발전소 쌍에 대한 거리를 측정
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = _distance(i, j);
            if (dist > m + 1e-9) continue;
    
            adj[i].push_back({j, dist});
            adj[j].push_back({i, dist});
        }
    }

    // 이미 연결되어 있는 station
    while (w--) {
        int u, v; cin >> u >> v;
        adj[--u].push_back({--v, 0});
        adj[v].push_back({u, 0});
    }

    cout << dijkstra(0, n - 1);

    return 0;
}